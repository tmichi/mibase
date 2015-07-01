/**
 * @file BooleanAttribute.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/BooleanAttribute.hpp>
#include <sstream>
namespace mi
{
        class BooleanAttribute::Impl
        {
        public:
                Impl ( bool& value ) : _value ( value )
                {
                        return;
                }

                ~Impl ( void )
                {
                        return;
                }

                bool& value ( void )
                {
                        return this->_value;
                }
        private:
                bool&    _value; ///< Value.
        };

        BooleanAttribute::BooleanAttribute ( const std::string& key,  bool& value ) : Attribute ( key ) , _implb ( new BooleanAttribute::Impl ( value ) )
        {
                return;
        }

        BooleanAttribute::~BooleanAttribute ( void )
        {
                if ( this->_implb != NULL ) {
                        delete this->_implb;
                        this->_implb = NULL;
                }

                return;
        }

        bool
        BooleanAttribute::parse ( const Argument& arg )
        {
                this->_implb->value() = arg.exist ( this->getKey() );
                return /* always */ true;
        }

        std::string
        BooleanAttribute::toString ( void ) const
        {
                std::stringstream ss;
                ss << this->getKey() << " : " << this->getValue();
                return ss.str();
        }

        std::string
        BooleanAttribute::getValue ( void ) const
        {
                return ( this->_implb->value() ) ? std::string ( "on" ) : std::string ( "off" );
        }

        BooleanAttribute&
        BooleanAttribute::setMessage ( const std::string& message )
        {
                Attribute::setMessage ( message ) ;
                return *this;
        }
}//namespace mi
