/**
 * @file Progress.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_PROGRESS_HPP
#define MI_PROGRESS_HPP 1
#include <string>

namespace mi
{
        /**
         * @class Progress Progress.hpp <mi/Progress.hpp>
         * @brief Display progress.
         */
        class Progress
        {
        private:
                class Impl;
                Progress ( const Progress& that );
                void operator = ( const Progress& that );
        public:
                /**
                 * @brief Constructor.
                 * @param [in] maxnum Maximum value of the counter.
                 * @param [in] width Display width.
                 */
                explicit Progress ( const int maxnum = 0 , const int width = 6 );
                /**
                 * @brief Destructor.
                 */
                ~Progress ( void );
                /**
                 * @brief Print progress.
                 */
                void print ( void );

                /*
                         * @brief Add counter.
                         * @retval true Success.
                         * @retval false Counter already reaches to the end..
                         */
                bool goNext ( void );
                /**
                 * @brief Add counter.
                 * @retval true Success.
                 * @retval false Counter already reaches to the end..
                 */
                bool addCounter ( void );
                inline std::string to_string ( void ) const;
        private:
                Impl* _impl;
        };
}
#endif// MI_PROGRESS_HPP
