/**
 * @file Progress.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_PROGRESS_HPP
#define MI_PROGRESS_HPP 1
#include <string>
#include <memory>
#include "NonCopyable.hpp"
namespace mi
{
        /**
         * @class Progress Progress.hpp <mi/Progress.hpp>
         * @brief Display progress.
	 *
         */
        class Progress : public NonCopyable
        {
        public:
                /**
                 * @brief Constructor.
                 * @param [in] maxSteps Maximum value of the counter.
                 * @param [in] width Display width.
                 */
                explicit Progress ( const int maxSteps = 0 , const int width = 6 );

                /**
                 * @brief Destructor.
                 */
                ~Progress ( void );

                /**
                 * @brief Print progress.
                 */
                void print ( void );

                /**
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
	private:
                /**
                 * @brief Get string
                 * @return String representation of progress.
                 */
                inline std::string to_string ( void ) const;
        private:
                class Impl;
		std::unique_ptr<Impl> _impl;
        };
}
#endif// MI_PROGRESS_HPP
