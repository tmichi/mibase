/**
 * @file Thread.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/Thread.hpp>


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)// Win32 API
#define OS_WINDOWS 1
#include <windows.h>
#include <process.h>
#define ThreadResult unsigned __stdcall
#else // POSIX supporing system.
#include <pthread.h>
#define stdcall  ///< Ignorable macro.
#define ThreadResult void*  ///<Thread result.
#endif

namespace mi
{
#ifdef OS_WINDOWS
        typedef HANDLE Handle; ///< Thread handle.
        typedef CRITICAL_SECTION CriticalSectionHandle; ///< Critical section handle.
#else
        typedef pthread_t Handle; ///< Thread handle.
        typedef pthread_mutex_t CriticalSectionHandle;///< Critical section handle.
#endif

        class Thread::Impl
        {
        public:
                Impl ( void )
                {
                        this->resetSequence();
                        return;
                }

                ~Impl ( void )
                {
                        return;
                }

                CriticalSectionHandle& getCSHandle ( void )
                {
                        return this->_cs;
                }

                void resetSequence ( void )
                {
                        this->_sequence = 0;
                }

                int getSequence ( void ) const
                {
                        const int result = this->_sequence;
                        const_cast<Thread::Impl*> ( this )->add_sequence();
                        return result;
                }

                void addHandle ( Handle handle )
                {
                        this->_handle.push_back ( handle );
                        return;
                }

                Handle& getHandle ( const int id )
                {
                        return this->_handle[id];
                }

                void reset ( void )
                {
                        this->_handle.clear();
                        this->resetSequence();
                        return;
                }

                int size ( void ) const
                {
                        return static_cast<int>(this->_handle.size());
                }
        private:
                void add_sequence ( void )
                {
                        this->_sequence += 1;
                }
        private:
                int         _sequence;
                std::vector<Handle>     _handle;
                CriticalSectionHandle	_cs;
        };

        Thread::Thread ( void ) : _impl ( new Thread::Impl() )
        {
                CriticalSectionHandle& cs = this->_impl->getCSHandle();
#ifdef OS_WINDOWS
                InitializeCriticalSection ( &cs );
#else //pthread
                pthread_mutex_init ( &cs, NULL );
#endif
                return;
        }

        Thread::~Thread ( void )
        {
                CriticalSectionHandle& cs = this->_impl->getCSHandle();
#ifdef OS_WINDOWS
                DeleteCriticalSection ( &cs );
#else //pthread
                pthread_mutex_destroy ( &cs );
#endif
                delete this->_impl;
                return;
        }

        void
        Thread::startCriticalSection ( void )
        {
                CriticalSectionHandle& cs = this->_impl->getCSHandle();
#ifdef OS_WINDOWS
                EnterCriticalSection ( &cs );
#else //pthread
                pthread_mutex_lock ( &cs );
#endif
                return;
        }

        void
        Thread::endCriticalSection ( void )
        {
                CriticalSectionHandle& cs = this->_impl->getCSHandle();
#ifdef OS_WINDOWS
                LeaveCriticalSection ( &cs );
#else //pthread
                pthread_mutex_unlock ( &cs );
#endif
                return;
        }

#ifdef OS_WINDOWS
        int
        Thread::createThread ( unsigned int ( __stdcall* func ) ( void* ), void* arglist )
        {
                this->startCriticalSection();
                Handle handle = ( Handle ) _beginthreadex ( NULL, 0, func, arglist, 0, NULL );
                this->_impl->addHandle ( handle );
                const int threadId = this->getNumThread() - 1;
                this->endCriticalSection();
                return threadId;
        }
#else
        int
        Thread::createThread ( void* ( * func ) ( void* ), void* arglist )
        {
                this->startCriticalSection();
                Handle handle;
                pthread_create ( &handle, NULL, ( void* ( * ) ( void* ) ) func, arglist );
                this->_impl->addHandle ( handle );
                const int threadId = this->getNumThread() - 1;
                this->endCriticalSection();
                return threadId;
        }
#endif
        void
        Thread::waitAll ( void )
        {
                for ( int i = 0 ; i  < this->getNumThread() ; i++ ) {
                        this->wait ( i );
                }

                return;
        }

        void
        Thread::wait ( const int id )
        {
                if ( id >= static_cast<int> ( this->getNumThread() ) ) {
                        return;
                }

#ifdef OS_WINDOWS
                WaitForSingleObject ( this->_impl->getHandle ( id ), INFINITE );
#else //pthread
                pthread_join ( this->_impl->getHandle ( id ), NULL );
#endif
                return;
        }


        void
        Thread::closeAll ( void )
        {
                for ( int i = 0 ; i  < this->getNumThread() ; i++ ) {
                        this->close ( i );
                }

                return;
        }

        bool
        Thread::close ( const int id ) const
        {
                if ( id >=  this->getNumThread( ) ) {
                        return false;
                }

#ifdef OS_WINDOWS
                return ( CloseHandle ( this->_impl->getHandle ( id ) ) != 0 );
#else //pthread
                return true;
#endif
        }

        void
        Thread::reset ( void )
        {
                this->waitAll();
                this->closeAll();
                this->_impl->reset();
                return;
        }

        int
        Thread::size ( void ) const
        {
                return this->_impl->size();
        }

        int
        Thread::getNumThread ( void ) const
        {
                return this->size();
        }

        int
        Thread::getSequence ( void )
        {
                this->startCriticalSection();
                const int result = this->_impl->getSequence();
                this->endCriticalSection();
                return result;
        }
        /**
         * @brief Reset the sequence.
         */

        void
        Thread::resetSequence ( void )
        {
                this->startCriticalSection();
                this->_impl->resetSequence();
                this->endCriticalSection();
                return;
        }
}
