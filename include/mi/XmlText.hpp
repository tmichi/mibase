#ifndef MI_XML_TEXT_HPP
#define MI_XML_TEXT_HPP 1
#include <string>
#include "XmlNode.hpp"
namespace mi
{
        class XmlText : public XmlNode
        {
        public:
                XmlText ( void );
                ~XmlText ( void );
                XmlNodeType getType  ( void ) const;
                bool isLeaf ( void ) const;
                void setText ( const std::string& text );
                const std::string& getText ( void ) const;
        private:
                class Impl;
                Impl *_impl;
        };
}
#endif// MI_XML_TEXT_HPP


