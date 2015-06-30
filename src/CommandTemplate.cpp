
/**
 * @file  CommandTemplate.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/CommandTemplate.hpp>
#include <iostream>
namespace mi
{
        class CommandTemplate::Impl
        {
        public:
                explicit Impl ( const std::string& cmdStr ) :  _cmdStr ( cmdStr ),  _isTimingModeOn ( false ), _isDebugModeOn ( false )
                {
                        return;
                }

                ~Impl ( void )
                {
                        return;
                }
                std::string getCommandStr( void ) const
                {
                        return this->_cmdStr;
                }

                AttributeSet& getAttributeSet ( void )
                {
                        return this->_attr;
                }

                Timer& getTimer ( void )
                {
                        return this->_timer;
                }

                void setTimingModeOn ( void )
                {
                        this->_isTimingModeOn = true;
                        return;
                }
                bool isTimingModeOn ( void ) const
                {
                        return this->_isTimingModeOn;
                }

                void setDebugModeOn ( void )
                {
                        this->_isDebugModeOn = true;
                        return;
                }
                bool isDebugModeOn ( void ) const
                {
                        return this->_isDebugModeOn;
                }

        private:
                std::string  _cmdStr; ///< Command name
                AttributeSet _attr;   ///< Attribute set.
                Timer        _timer;///< Timer.
                bool         _isTimingModeOn; ///< Flag for timing mode.
                bool         _isDebugModeOn;///< Flag for debug mode.
        };
        CommandTemplate::CommandTemplate ( const std::string& cmdStr )
        {
                return;
        }

        CommandTemplate::~CommandTemplate ( void )
        {
                std::ostream& out = std::cerr;
                if ( this->isTimingModeOn() ) {
                        this->getTimer().end ( "total" );
                        this->getTimer().printAll ( 4, mi::TIME_SECOND, out );
                }
                out << "peakMemory : " << SystemInfo::getPeakMemorySize() << "[mb]" << std::endl;

                if ( this->_impl != NULL ) {
                        delete this->_impl;
                        this->_impl = NULL;
                }
                return;
        }

        AttributeSet&
        CommandTemplate::getAttributeSet ( void )
        {
                return this->_impl->getAttributeSet();
        }

        Timer&
        CommandTemplate::getTimer ( void )
        {
                return this->_impl->getTimer();
        }

        bool
        CommandTemplate::isTimingModeOn ( void ) const
        {
                return this->_impl->isTimingModeOn();
        }

        bool
        CommandTemplate::isDebugModeOn ( void ) const
        {
                return this->_impl->isDebugModeOn();
        }

        CommandTemplate&
        CommandTemplate::setTimingModeOn ( void )
        {
                this->_impl->setTimingModeOn();
                this->getTimer().init();
                this->getTimer().start ( "total" );
                return *this;
        }

        CommandTemplate&
        CommandTemplate::setDebugModeOn ( void )
        {
                this->_impl->setDebugModeOn();
                return *this;
        }

        void
        CommandTemplate::usage ( void )
        {
                this->getAttributeSet().printUsage ( this->_impl->getCommandStr() );
                return;
        }

        int
        CommandTemplate::execute ( CommandTemplate& cmd, Argument& arg )
        {
                // Message mode
                if ( arg.exist ( "--debug" ) ) {
                        cmd.setDebugModeOn();
                        std::cerr << "debug mode on." << std::endl;
                }
                if ( arg.exist ( "--timing" ) ) {
                        cmd.setTimingModeOn();
                }
                /*        if ( arg.exist ( "--version" ) ) {
                            cmd.version();
                            return 1;
                	    }*/
                if ( arg.exist ( "--help" ) ) {
                        cmd.usage();
                        return 2;
                }
                if ( !cmd.init ( arg ) ) {
                        std::cerr << "initialization failed." << std::endl;
                        cmd.usage();
                        return -1;
                }
                if ( !cmd.run()  ) {
                        std::cerr << "main routine failed." << std::endl;
                        return -2;
                }
                if ( !cmd.term() ) {
                        std::cerr << "termination failed." << std::endl;
                        return -3;
                }
                return 0;
        }
}//namespace mi
