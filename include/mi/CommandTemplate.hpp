/**
* @file  CommandTemplate.hpp
* @author Takashi Michikawa <michikawa@acm.org>
*/
#pragma once
#ifndef MI_COMMAND_TEMPLATE_HPP
#define MI_COMMAND_TEMPLATE_HPP 1

#include <cstdlib>
#include <memory>

#include "Argument.hpp"
#include "AttributeSet.hpp"
#include "SystemInfo.hpp"
#include "Timer.hpp"
#include "NonCopyable.hpp"
/**
 * @namespace mi
 * @brief Namespace of codes those I created.
 */
namespace mi
{
        /**
        * @class CommandTemplate CommandTemplate.hpp <mi/CommandTemplate.hpp>
        * @brief Template for CUI-based command.
        */
        class CommandTemplate : public NonCopyable
        {
        public:
                /**
                * @brief Constructor.
                */
                explicit CommandTemplate ( const std::string& cmdStr = "a.out" );
                /**
                * @brief Destructor.
                */
                virtual ~CommandTemplate ( void );
        protected:
                /**
                 * @brief Initialize the command.
                 * @param [in] arg Argument.
                 * @retval true Success.
                 * @retval false Failure.
                 */
                virtual bool init ( const Argument& arg ) = 0;
                /**
                 * @brief Run the command.
                 * @retval true Success.
                 * @retval false Failure.
                 */
                virtual bool run  ( void ) = 0;
                /**
                 * @brief Terminate the command.
                 * @retval true Success.
                 * @retval false Failure.
                 */
                virtual bool term ( void ) = 0;

                /**
                 * @brief Get attribute set.
                 * @return A reference to the attribute set.
                 */
                AttributeSet& getAttributeSet ( void );
                /**
                 * @brief Get timer object.
                 * @return A reference to the timer.
                 */
                Timer& getTimer ( void );
                /**
                * @brief Check the timing mode
                * @retval true On.
                * @retval true Off.
                */
                bool isTimingModeOn ( void ) const;

                bool isDebugModeOn ( void ) const;
                /**
                * @brief Set timing mode on.
                */
                CommandTemplate& setTimingModeOn ( void );


                /**
                * @brief Print usage.
                */
                CommandTemplate& setDebugModeOn ( void );
        private:
                /**
                * @brief Print usage.
                */
                void usage ( void );
        public:
                /**
                * @brief Template procedure from initialization to termination.
                * @param [in] cmd Instance.
                * @param [in] arg Argument.
                * @retval 2 Success. Version information called.
                * @retval 1 Success. Usage called.
                * @retval 0 Success. Execution succeeded.
                * @retval -1 Failure. Initialzation  failed.
                * @retval -2 Failure. Running failed.
                * @retval -3 Failure. Termination failed.
                */
                static int execute ( CommandTemplate& cmd, Argument& arg );
        private:
                class Impl;
		std::unique_ptr<Impl> _impl;
        };//class CommandTemplate
}//namespace mi
#endif // MI_COMMAND_TEMPLATE_HPP
