/**
 * @file Timer.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_TIMER_HPP
#define MI_TIMER_HPP 1

#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <chrono>

#include "NonCopyable.hpp"
namespace mi
{
        typedef std::chrono::high_resolution_clock::time_point clock_time_t;

        /**
         * @brief Time format.
         */
        enum time_format {
                TIME_SECOND, ///< Seconds.
                TIME_MINUTE, ///< Minutes.
                TIME_HOUR,   ///< Hours.
                TIME_DAY,    ///< Days.
                TIME_AUTO    ///< Default.
        };
        /**
         * @class Timer Timer.hpp <mi/Timer.hpp>
         * @brief Timer object.
         *
         * This class can be used for measuring time.  The precision
         * is much better than the use of clock (), since we wrap more
         * accurate functions.  When you measure computation time of a
         * step, insert Timer::start("key") and Timer::end("key")
         * before and after the part.
         *
         * Here shows an example code :
         * @code
         *    mi::Timer timer;
         *    timer.start("hoge");
         *    hoge(); // do something
         *    timer.end("hoge");
         *    timer.print("hoge");
         * @endcode
         *
         */
        class Timer : public NonCopyable
        {
        public:
                /**
                 * @brief Constructor.
                 */

                Timer ( void );
                /**
                 * @brief Destructor.
                 */
                ~Timer ( void );
                /**
                 * @brief Initialize Timer object.
                 */
                void init ( void );
                /**
                 * @brief Start measurement.
                 * @param [in] key Key string for the measurement.
                 * @retval true Success.
                 * @retval false Failure. The key already exists.
                 */
                bool start ( const std::string& key );

                /**
                 * @brief End measurement.
                 * @param [in] key Key string for the measurement.
                 * @retval true Success.
                 * @retval false Failure. The key does not exist.
                 */
                bool end ( const std::string& key );
                /**
                 * @brief Get the time associated with the key
                 * @param [in] key Key string for the measurement.
                 * @param [in] format Time format.
                 * @return Computation time.
                 * @retval false Failure. The measurement is not finished or does not exist.
                 */
                double get ( const std::string& key , const time_format format = TIME_SECOND );

                /**
                 * @brief Print measurement.
                 * @param [in] key Key
                 * @param [in] digit Digit
                 * @param [in] format Time format
                 * @param [in] out Output stream
                 */
                void print ( const std::string& key, const int digit = 4, const time_format format = TIME_AUTO, std::ostream& out = std::cout );
                /**
                 * @brief Print all measurements
                 * @param [in] digit Digit
                 * @param [in] format Time format
                 * @param [in] out Output stream
                 */
                void printAll ( const int digit = 4, const time_format format = TIME_AUTO, std::ostream& out = std::cout );

                /**
                 * @brief Get measurement result as string format.
                 * @param [in] key Key. Print nothing when key does not match.
                 * @param [in] digit Digit.
                 * @param [in] format Time format.
                 */
                std::string toString ( const std::string& key, const int digit = 6, const time_format format = TIME_AUTO );
        private:
                /**
                 * @brief Check the key exists.
                 * @retval true The key exists.
                 * @retval false The key does not exist.
                 */
                bool exist ( const std::string& key ) const;

//                clock_time_t get_elapsed_time ( void ) const;

                time_format estimate_format ( const double t ) const;
                std::string get_format_string ( const time_format format ) const;
        private:
                const static int TIMER_MINUTE = 60;//seconds.
                const static int TIMER_HOUR   = 60;//minutes.
                const static int TIMER_DAY    = 24;//hours

                class Impl;
		std::unique_ptr<Impl> _impl;
        };
};
#endif //MI_TIME_HPP
