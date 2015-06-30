/**
 * @file StringAttribute.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/StringAttribute.hpp>
#include <sstream>
namespace mi
{
        class StringAttribute::Impl
        {
        private:
                Impl ( const Impl& that ) ;
                void operator = ( const Impl& that ) ;
        public:
                Impl ( std::string& value ) : _value ( value )
                {
                        return;
                }

                ~Impl ( void )
                {
                        return;
                }

                std::string& value ( void )
                {
                        return this->_value;
                }

                std::string& defaultValue ( void )
                {
                        return this->_defaultValue;
                }
        private:
                std::string&    _value; ///< Value.
                std::string     _defaultValue; ///< Default value.
        };

        StringAttribute::StringAttribute ( const std::string& key,  std::string& value ) : Attribute ( key ) , _impls ( new StringAttribute::Impl ( value ) )
        {
                return;
        }

        StringAttribute::~StringAttribute ( void )
        {
                if ( this->_impls != NULL ) {
                        delete this->_impls;
                        this->_impls = NULL;
                }
                return;
        }

        bool
        StringAttribute::parse ( const Argument& arg )
        {
                if ( this->is_key_found ( arg, this->getKey(), 1 ) ) {
                        this->_impls->value() = arg.get<std::string> ( this->getKey() );
                        return true;
                } else {
                        if ( this->isMandatory() ) {
                                this->setErrorCode ( ATTRIBUTE_ERROR_KEY_NOT_FOUND );
                                return false;
                        } else {
                                this->_impls->value() = this->_impls->defaultValue();
                                return true;
                        }
                }
        }

        StringAttribute&
        StringAttribute::setDefaultValue ( const std::string& defaultValue )
        {
                this->_impls->defaultValue() = defaultValue;
                return *this;
        }

        StringAttribute&
        StringAttribute::setMandatory ( void )
        {
                Attribute::setMandatory();
                return *this;
        }
        StringAttribute&
        StringAttribute::setHidden ( void )
        {
                Attribute::setHidden();
                return *this;
        }

        StringAttribute&
        StringAttribute::setMessage ( const std::string& message )
        {
                Attribute::setMessage ( message ) ;
                return *this;
        }

        std::string
        StringAttribute::toString ( void ) const
        {
                std::stringstream ss;
                ss << this->getKey() << " : " << this->getValue();
                return ss.str();
        }

        std::string
        StringAttribute::getValue ( void ) const
        {
                return this->_impls->value();
        }
}
