#include "XmlElement.hpp"
#include "XmlAttribute.hpp"
namespace mi
{
        XmlElement::XmlElement( const std::string& name ) : XmlNode ( name )
        {
                return;
        }

        XmlElement::~XmlElement ( void )
        {
                return;
        }

        void
        XmlElement::setAttribute ( const std::string& name, const std::string& value )
        {
                mi::XmlAttribute *attr = new mi::XmlAttribute( "name" );
                //@todo check が必要
                this->appendChild( attr );
                attr->setValue( value );
        }
        std::string
        XmlElement::getAttribute ( const std::string& name ) const
        {
                XmlElement* element = const_cast<XmlElement*>( this );
                mi::XmlNode* node0 = element->getFirstChildNode();
                if ( node0 != NULL ) {
                        if ( node0->getNodeType() == mi::XmlNodeAttribute ) {
                                XmlAttribute* attr = dynamic_cast<XmlAttribute*> ( node0 );
                                if ( attr->getName().compare( name ) == 0  ) return attr->getValue();
                        }
                        node0 =  element->getFirstChildNode()->getNextSiblingNode();
                        while ( node0 != NULL ) {
                                if ( node0->getNodeType() == mi::XmlNodeAttribute ) {
                                        XmlAttribute* attr = dynamic_cast<XmlAttribute*> ( node0 );
                                        if ( attr->getName().compare( name ) == 0  ) return attr->getValue();
                                }
                                node0 = node0->getNextSiblingNode();
                        }
                }
                return std::string();
        }

        std::string
        XmlElement::getTagName( void ) const
        {
                return this->getNodeName();
        }

        XmlNodeType
        XmlElement::getNodeType ( void ) const
        {
                return mi::XmlNodeElement;
        }
};
