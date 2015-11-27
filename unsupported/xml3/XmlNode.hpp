#ifndef MI_XML_NODE_HPP
#define MI_XML_NODE_HPP 1
#include "xml.hpp"
namespace mi
{
        class XmlNode
        {
        private:
                void operator=( const XmlNode& node );
                XmlNode( const XmlNode& node );
        protected:
                XmlNode ( void )
                {
                        return;
                }
        public:
                virtual ~XmlNode ( void )
                {
                        return;
                }

                virtual XmlNodeType getType ( void ) const
                {
                        return InvalidNode;
                }

                virtual bool isLeaf( void ) const = 0;
        };
}
#endif// MI_XML_NODE_HPP


