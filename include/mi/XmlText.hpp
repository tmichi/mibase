#ifndef MI_XML_TEXT_HPP
#define MI_XML_TEXT_HPP 1
#include <string>
#include "XmlNode.hpp"
namespace mi
{
        class XmlText : public XmlNode
        {
        public:
                /**
                 * @brief Constructor
                 */
                XmlText ( void );
                /**
                 * @brief Destructor
                 */
                ~XmlText ( void );
                /**
                 * @brief Get node type
                 */
                XmlNodeType getType  ( void ) const;
                /**
                 * @brief Check this is leaf node
                 */
                bool isLeaf ( void ) const;
                /**
                 * @brief Set text
                 * @param [in] text Text
                 */
                void setText ( const std::string& text );
                /**
                 * @brief Get text
                 * return Text
                 */
                const std::string& getText ( void ) const;
        private:
                class Impl;
                Impl *_impl;
        };
}
#endif// MI_XML_TEXT_HPP


