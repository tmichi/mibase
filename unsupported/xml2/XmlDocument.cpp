#include "XmlDocument.hpp"
#include <iostream>
namespace mi
{
        XmlDocument::XmlDocument( void ) : XmlNode()
        {
                return;
        }

        XmlDocument::~XmlDocument ( void )
        {
                return;
        }

        XmlElement*
        XmlDocument::getDocumentElement( void )
        {
                XmlNode* child =  this->getFirstChildNode();
                if ( child->getNodeType() != mi::XmlNodeElement ) {
                        std::cerr << child->getNodeType() << std::endl;
                        return NULL;
                }
                return ( XmlElement* )child;
        }

        XmlNodeType
        XmlDocument::getNodeType ( void ) const
        {
                return mi::XmlNodeDocument;
        }
}
