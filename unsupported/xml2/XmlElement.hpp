#ifndef MI_XML_ELEMENT_HPP
#define MI_XML_ELEMENT_HPP 1
#include "XmlNode.hpp"
namespace mi
{
        class XmlElement : public XmlNode
        {
        public:
                XmlElement( const std::string& name );
                virtual ~XmlElement ( void ) ;
                void setAttribute ( const std::string& name, const std::string& value ) ;
                std::string getAttribute ( const std::string& name ) const ;
                //XmlAttribute* getAttribute ( const std::string& name ) const ;
                std::string getTagName( void ) const;
                virtual XmlNodeType getNodeType ( void ) const;
        private:
                class Impl;
                Impl* _impl;
        };
};
#endif// MI_XML_ELEMENT_HPP
