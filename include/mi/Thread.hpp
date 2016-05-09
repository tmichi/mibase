/**
 * @file Thread.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
//C4530
#ifndef MI_THREAD_HPP
#define MI_THREAD_HPP 1
#include <memory>
#include "NonCopyable.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)// Win32 API
#define ThreadResult unsigned __stdcall
#define OS_WINDOWS 1
#else // POSIX supporing system.
#define ThreadResult void*  ///<Thread result.
#define stdcall  ///< Ignorable macro.
#endif
namespace mi
{
        /**
         * @class Thread Thread.hpp "mi/Thread.hpp"
         * @brief Thread object.
         */
        class Thread : public NonCopyable
        {
        public:
                /**
                 * @brief Constructor.
                 */
                explicit Thread ( void );
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
		std::unique_ptr<Impl> _impl;
        };
}
#endif // MI_THREAD_HPP
