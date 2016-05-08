#ifndef MI_XML_NODE_HPP
#define MI_XML_NODE_HPP 1
namespace mi
{
        enum XmlNodeType {
                InvalidNode,
                ElementNode,
                TextNode
        };

        class XmlNode
        {
        private:
                void operator = ( const XmlNode& node );
                XmlNode ( const XmlNode& node );
        protected:
                XmlNode ( void );
        public:
                /**
                 * @brief Destructor
                 */
                virtual ~XmlNode ( void );
                virtual XmlNodeType getType ( void ) const = 0;
                virtual bool isLeaf ( void ) const = 0;
        };
}
#endif// MI_XML_NODE_HPP


