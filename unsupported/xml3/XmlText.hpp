#ifndef MI_XML_TEXT_HPP
#define MI_XML_TEXT_HPP 1
#include "xml.hpp"
#include "XmlNode.hpp"

#include <string>

namespace mi
{
        class XmlText : public XmlNode
        {
        public:
                XmlText ( void ) : XmlNode(), _text ( std::string() )
                {
                        return;
                }

                ~XmlText ( void )
                {
                        return;
                }

                XmlNodeType getType  ( void ) const
                {
                        return TextNode;
                }

                bool isLeaf ( void ) const
                {
                        return true;
                }

                void setText ( const std::string& text )
                {
                        this->_text = text;
                }

                const std::string& getText ( void ) const
                {
                        return this->_text;
                }
        private:
                std::string _text;
        };
};
#endif// MI_XML_TEXT_HPP


