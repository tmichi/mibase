
/**
 * @file  CommandTemplate.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/CommandTemplate.hpp>
#include <iostream>
namespace mi
{
        CommandTemplate::CommandTemplate ( const std::string& cmdStr ) : _cmdStr ( cmdStr ),  _isTimingModeOn ( false ), _isDebugModeOn ( false )
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
                return;
        }

        AttributeSet&
        CommandTemplate::getAttributeSet ( void )
        {
                return this->_attr;
        }

        Timer&
        CommandTemplate::getTimer ( void )
        {
                return this->_timer;
        }

        bool
        CommandTemplate::isTimingModeOn ( void ) const
        {
                return this->_isTimingModeOn;
        }

        bool
        CommandTemplate::isDebugModeOn ( void ) const
        {
                return this->_isDebugModeOn;
        }

        CommandTemplate&
        CommandTemplate::setTimingModeOn ( void )
        {
                this->_isTimingModeOn = true;
                if ( this->isTimingModeOn() ) {
                        this->getTimer().init();
                        this->getTimer().start ( "total" );
                }
                return *this;
        }

        CommandTemplate&
        CommandTemplate::setDebugModeOn ( void )
        {
                this->_isDebugModeOn = true;
                return *this;
        }

        void
        CommandTemplate::usage ( void )
        {
                this->getAttributeSet().printUsage ( this->_cmdStr );
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


