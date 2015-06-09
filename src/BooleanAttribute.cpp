/**
 * @file BooleanAttribute.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/BooleanAttribute.hpp>
namespace mi {

        BooleanAttribute::BooleanAttribute ( const std::string& key,  bool& value ) : Attribute ( key ) , _value ( value ) {
                return;
        }

        bool
        BooleanAttribute::parse ( const Argument& arg ) {
                this->_value = arg.exist ( this->getKey() );
                return /* always */ true;
        }

        std::string
        BooleanAttribute::toString ( void ) const {
                std::stringstream ss;
                ss << this->getKey() << " : ";
                if ( this->_value ) ss << "on";
                else ss << "off";
                return ss.str();
        }
        std::string
        BooleanAttribute::getValue ( void ) const {
                return ( this->_value ) ? std::string ( "on" ) : std::string ( "off" );
        }

        BooleanAttribute&
        BooleanAttribute::setMessage ( const std::string& message ) {
                Attribute::setMessage ( message ) ;
                return *this;
        }
}//namespace mi

