#ifndef XML_TEXT_HPP
#define XML_TEXT_HPP 1
#include "XmlNode.hpp"
namespace mi
{
        class XmlText : public XmlNode
        {
        public:
                XmlText ( void );
                ~XmlText ( void );
                void setData ( const std::string& data );
                std::string getData ( void ) const ;
                mi::XmlNodeType getNodeType ( void ) const;
        private:
                std::string _str;
        };
}

#endif //XML_TEXT_HPP
