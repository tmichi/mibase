/**
 * @file Thread.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
//C4530
#ifndef MI_THREAD_HPP
#define MI_THREAD_HPP 1

#include <vector>

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
        /**
         * @class Thread Thread.hpp "mi/Thread.hpp"
         * @brief Thread object.
         */
        class Thread
        {
        public:
                /*
                #ifdef OS_WINDOWS
                                typedef HANDLE Handle; ///< Thread handle.
                                typedef CRITICAL_SECTION CriticalSectionHandle; ///< Critical section handle.
                #else
                                typedef pthread_t Handle; ///< Thread handle.
                                typedef pthread_mutex_t CriticalSectionHandle;///< Critical section handle.
                #endif
                */
        private:
                Thread ( const Thread& that ) ;
                void operator = ( const Thread& that ) ;
        public:
                /**
                 * @brief Constructor.
                 */
                Thread ( void );
                /**
                 * @brief Destructor.
                 */
                ~Thread ( void );
                /**
                 * @brief Start critical section here.
                 * @sa Thread::endCriticalSection()
                 */
                void startCriticalSection ( void );
                /**
                 * @brief End critical section here.
                 * @sa Thread::startCriticalSection()
                 */
                void endCriticalSection ( void );
                /**
                 * @brief Create new thread.
                 * @param [in] func Function.
                 * @param [in] arglist Argument list.
                 * @return Thread ID.
                 */
#ifdef OS_WINDOWS
                int createThread ( unsigned int ( __stdcall* func ) ( void* ), void* arglist );
#else
                int createThread ( void* ( * func ) ( void* ), void* arglist );
#endif
                /**
                 * @brief Wait all threads are terminated.
                 */
                void waitAll ( void );
                /**
                 * @brief Wait a thread is terminated.
                 * @param [in] id Thread ID.
                 */
                void wait ( const int id );
                /**
                 * @brief Close all threads.
                 */
                void closeAll ( void );

                /**
                 * @brief Close a thread.
                 * @param [in] id Thread ID.
                 */
                bool close ( const int id ) const;
                /**
                 * @brief Reset threads.
                 */
                void  reset ( void );
                /**
                 * @brief Get the number of threads.
                 * @return Numrber of threads.
                 */
                int size ( void ) const;
                /**
                 * @brief Get the number of threads.
                 * @return Numrber of threads.
                 */
                int getNumThread ( void ) const;
                /**
                 * @brief Get a number of sequence.
                 * @return Number.
                 * @note This function is thread-safe or the number is always unique.
                 */
                int getSequence ( void );
                /**
                 * @brief Reset the sequence.
                 */
                void resetSequence ( void );
        private:
                class Impl;
                Impl* _impl;
        };
}
#endif // MI_THREAD_HPP
