#include <mi/Routine.hpp>
#include <mi/Timer.hpp>
#include <sstream>
#include <iostream>
namespace mi
{
        class Routine::Impl
        {
        private:
                const std::string _name;
		std::string _tempFile;
                bool _status;
                std::stringstream _ss;
        private:
                Impl ( const Impl& that );
                void operator = ( const Impl& that );
        public:
                Impl ( const std::string& name ) : _name ( name ), _tempFile("routine"), _status ( true )
                {
                        return;
                }

                std::string getName ( void ) const
                {
                        return this->_name;
                }

                std::stringstream& getStream ( void )
                {
                        return this->_ss;
                }

                bool getStatus ( void ) const
                {
                        return this->_status;
                }

                void setFailed ( void )
                {
                        this->_status = false;
                }

		std::string& tempFile(void) {
			return this->_tempFile;
		}

                static Timer& getTimer ( void )
                {
                        static Timer timer;
                        return timer;
                }

                static bool& debug_mode ( void )
                {
                        static bool isDebugMode = false;
                        return isDebugMode;
                }

        };

        Routine::Routine ( const std::string& name ) : NonCopyable(), _impl ( new Impl ( name ) )
        {
                Routine::Impl::getTimer().start ( this->_impl->getName() );
                std::cerr << this->_impl->getName() << " routine ... ";
                return;
        }

        Routine::~Routine ( void )
        {
                Routine::Impl::getTimer().end ( this->_impl->getName() );
                if ( this->check() ) {
                        std::cerr << " done." << std::endl;
                } else  {
                        std::cerr << " failed." << std::endl;;
                        std::cerr << this->_impl->getStream().str() << std::endl;
                }
                return ;
        }

        Routine*
        Routine::getInstance ( void )
        {
                return this;
        }

        bool
        Routine::run ( Routine* routine )
        {
                if ( ! routine->check() ) {
                        return false;
                }

                return routine->run_main_routine();
        }

        bool
        Routine::check ( void ) const
        {
                return this->_impl->getStatus();
        }

        void
        Routine::setDebugModeOn ( void )
        {
                Routine::Impl::debug_mode() = true;
                return;
        }

	Routine&
	Routine::setTempFileNameHeader ( const std::string& fileName ) {
		this->_impl->tempFile() = fileName;
		return *this;
	}


	std::string 
	Routine::create_temp_file_name ( const std::string& footer ) const {
		std::stringstream ss;
		ss << this->_impl->tempFile()<<footer;
		return ss.str();
	}

        std::stringstream&
        Routine::stream ( void )
        {
                return this->_impl->getStream();
        }

        bool
        Routine::run_main_routine ( void )
        {
                this->set_failed();
                return this->_impl->getStatus();
        }

        void
        Routine::set_failed ( void )
        {
                this->_impl->setFailed();
                return;
        }

        bool
        Routine::is_debug_mode ( void )
        {
                return Routine::Impl::debug_mode();
        }

}


