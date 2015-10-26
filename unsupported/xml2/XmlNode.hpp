#ifndef MI_XML_NODE_HPP
#define MI_XML_NODE_HPP 1
#include <string>
#include <vector>
#include <map>

namespace mi
{
        enum XmlNodeType {
                XmlNodeElement,
                XmlNodeText,
                XmlNodeAttribute,
                XmlNodeComment,
                XmlNodeDocument,
                XmlNodeInvalid
        };
        class XmlDocument;
        class XmlNode
        {
        private:
                XmlNode( const XmlNode& that );
                void operator = ( const XmlNode& that );
        public:
                explicit XmlNode( const std::string& name = std::string() );
                virtual ~XmlNode ( void ) ;

                XmlNode* getFirstChildNode( void );
                XmlNode* getNextSiblingNode( void );
                XmlNode* getParentNode( void );

                virtual XmlNodeType getNodeType ( void ) const;
                std::string getNodeName ( void ) const;
                std::string getNodeValue( void ) const;

                XmlDocument* getOwnerDocument ( void );
                XmlNode* appendChild( XmlNode* newChild ) ;


                // Node* insertBefore ( Node* newNode, Node* refChild)
                // Node* replaceChild ( Node* newNode, Node* refChild)
                // Node* removeChild  ( Node* oldChild)

                //NamedNodeMap* getAttributes ();
        private:
                class Impl;
                Impl* _impl;
        };
};
#endif// MI_XML_NODE_HPP
