#include <mi/Attribute.hpp>
#include <string>
#include <sstream>
#include <iostream>

namespace mi
{
        Attribute::Attribute ( const std::string& key ) : _key ( key ), _isMandatory ( false ), _isHidden ( false ), _errorCode ( ATTRIBUTE_ERROR_OK )
        {
                return ;
        }

        Attribute::~Attribute ( void )
        {
                return;
        }

        Attribute&
        Attribute::setMandatory ( void )
        {
                this->_isMandatory = true;
                return *this;
        }

        Attribute&
        Attribute::setHidden ( void )
        {
                this->_isHidden = true;
                return *this;
        }

        void
        Attribute::printError ( void )
        {
                switch ( this->getErrorCode() ) {
                case ATTRIBUTE_ERROR_OK :
                        break;
                case ATTRIBUTE_ERROR_KEY_NOT_FOUND :
                        std::cerr << this->getKey() << " was not found." << std::endl;
                        break;
                case ATTRIBUTE_ERROR_VALUE_OUT_OF_RANGE :
                        std::cerr << "key value " << this->getValue() << " (for " << this->getKey() << ") is out-of-range." << std::endl;
                        break;
                default : //  ATTRIBUTE_ERROR_INVALID
                        std::cerr << "unknown error found." << std::endl;
                        break;
                }
                return;
        }

        void
        Attribute::print ( std::ostream& out )
        {
                out << this->toString() << std::endl;
        }


        std::string
        Attribute::getKey ( void ) const
        {
                return this->_key;
        }

        std::string
        Attribute::getValue ( void ) const
        {
                return std::string();
        }

        bool
        Attribute::isMandatory ( void ) const
        {
                return this->_isMandatory;
        }

        bool
        Attribute::is_key_found ( const Argument& arg, const std::string& key, int offset )
        {
                return arg.exist ( key, offset );
        }


        AttributeErrorCode
        Attribute::getErrorCode ( void  ) const
        {
                return this->_errorCode;
        }

        void
        Attribute::setErrorCode ( const AttributeErrorCode code )
        {
                this->_errorCode = code;
                return;
        }



        void
        Attribute::setMessage ( const std::string& message )
        {
                this->_message = message;
                return;
        }

        std::string
        Attribute::getMessage ( void ) const
        {
                return this->_message;
        }

        void
        Attribute::print_usage ( void )
        {
                if ( this->_isHidden ) return;
                std::cerr << "\t" << this->getKey() << "\t" << this->getMessage() << std::endl;
        }
}

