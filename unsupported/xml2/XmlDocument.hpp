#ifndef MI_XML_DOCUMENT_HPP
#define MI_XML_DOCUMENT_HPP 1
#include "XmlNode.hpp"
#include "XmlElement.hpp"
namespace mi
{
        class XmlDocument : public XmlNode
        {
        private:
                XmlDocument ( const XmlDocument& that ) ;
                void operator = ( const XmlDocument& that ) ;
        public:
                explicit XmlDocument( void );
                ~XmlDocument ( void );
                XmlElement* getDocumentElement( void );
                XmlNodeType getNodeType( void ) const;
        };
}
#endif // MI_XML_DOCUMENT_HPP
