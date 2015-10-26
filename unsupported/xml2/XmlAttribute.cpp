#include "XmlAttribute.hpp"
#include "XmlText.hpp"
#include "XmlElement.hpp"
namespace mi
{
        XmlAttribute::XmlAttribute( const std::string& name ) : XmlNode( name )
        {
                XmlText *node = new XmlText();
                this->appendChild( node );
                return;
        }
        XmlAttribute::~XmlAttribute ( void )
        {
                return;
        }
        XmlElement*
        XmlAttribute::getOwnerElement( void )
        {
                return dynamic_cast<XmlElement*>( this->getParentNode() );
        }
        std::string
        XmlAttribute::getName( void ) const
        {
                return this->getNodeName();
        }

        std::string
        XmlAttribute::getValue ( void ) const
        {
                XmlAttribute* attr = const_cast<XmlAttribute*>( this );
                XmlNode* node = attr->getFirstChildNode();
                return dynamic_cast<XmlText*>( node )->getData();
        }

        void
        XmlAttribute::setValue( const std::string& value )
        {
                dynamic_cast<XmlText*>( this->getFirstChildNode() )->setData( value );
        }

        XmlNodeType
        XmlAttribute::getNodeType ( void ) const
        {
                return mi::XmlNodeAttribute;
        }
}
