#ifndef MI_XML_NODE_HPP
#define MI_XML_NODE_HPP 1
#include "NonCopyable.hpp"
#include <memory>
namespace mi
{
        enum XmlNodeType {
                InvalidNode,
                ElementNode,
                TextNode
        };

        class XmlNode : public NonCopyable
        {
        protected:
                /**
                 * @brief Constructor
                 */
                XmlNode ( void );
        public:
                /**
                 * @brief Destructor
                 */
                virtual ~XmlNode ( void );
                /**
                 * @brief Get type of the node.
                 */
                virtual XmlNodeType getType ( void ) const = 0;
                /**
                 * @brief Return the node is leaf or not.
                 */
                virtual bool isLeaf ( void ) const = 0;
        };
}
#endif// MI_XML_NODE_HPP


