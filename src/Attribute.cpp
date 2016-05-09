#include <mi/Attribute.hpp>
#include <string>
#include <sstream>
#include <iostream>

namespace mi
{
        class Attribute::Impl
        {
        public:
                Impl ( const std::string& key ) : _key ( key ), _isMandatory ( false ), _isHidden ( false ), _errorCode ( ATTRIBUTE_ERROR_OK )
                {
                        return;
                }

                ~Impl ( void )
                {
                        return;
                }

                std::string getKey ( void ) const
                {
                        return this->_key;
                }

                void setMessage ( const std::string& message )
                {
                        this->_message = message;
                        return;
                }

                std::string getMessage ( void ) const
                {
                        return this->_message;
                }

                void setMandatory ( void )
                {
                        this-> _isMandatory = true;
                }

                bool isMandatory ( void ) const
                {
                        return this->_isMandatory;
                }

                void setHidden ( void )
                {
                        this->_isHidden = true;
                }

                bool isHidden ( void )
                {
                        return this->_isHidden;
                }

                void setErrorCode ( const AttributeErrorCode code )
                {
                        this->_errorCode = code;
                }

                AttributeErrorCode getErrorCode ( void )
                {
                        return this->_errorCode;
                }
        private:
                const std::string  _key;        ///< Key string.
                std::string        _message;    ///< Message for the attribute.
                bool               _isMandatory;///< Flag this is mandatory attribute.
                bool               _isHidden;   ///< This is a hidden attribute.
                AttributeErrorCode _errorCode;  ///< Error code
        };


        Attribute::Attribute ( const std::string& key ) : _impl ( new Attribute::Impl ( key ) )
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
                this->_impl->setMandatory();
                return *this;
        }

        Attribute&
        Attribute::setHidden ( void )
        {
                this->_impl->setHidden();
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
                return this->_impl->getKey();
        }

        std::string
        Attribute::getValue ( void ) const
        {
                return std::string();
        }

        bool
        Attribute::isMandatory ( void ) const
        {
                return this->_impl->isMandatory();
        }

        bool
        Attribute::is_key_found ( const Argument& arg, const std::string& key, int offset )
        {
                return arg.exist ( key, offset );
        }


        AttributeErrorCode
        Attribute::getErrorCode ( void  ) const
        {
                return this->_impl->getErrorCode();
        }

        void
        Attribute::setErrorCode ( const AttributeErrorCode code )
        {
                this->_impl->setErrorCode ( code );
                return;
        }



        Attribute&
        Attribute::setMessage ( const std::string& message )
        {
                this->_impl->setMessage ( message );
                return *this;
        }

        std::string
        Attribute::getMessage ( void ) const
        {
                return this->_impl->getMessage();
        }

        void
        Attribute::print_usage ( void )
        {
                if ( ! this->_impl->isHidden() ) {
                        std::cerr << "\t" << this->getKey() << "\t" << this->getMessage() << std::endl;
                }

                return;
        }
}
