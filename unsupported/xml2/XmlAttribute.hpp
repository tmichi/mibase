#ifndef MI_XML_ATTRIBUTE_HPP
#define MI_XML_ATTRIBUTE_HPP 1
#include "XmlNode.hpp"
namespace mi
{
        class XmlElement;
        class XmlAttribute : public XmlNode
        {
        public:
                XmlAttribute( const std::string& name );
                virtual ~XmlAttribute ( void ) ;
                XmlElement* getOwnerElement( void );
                std::string getName( void ) const;
                std::string getValue ( void ) const;
                void setValue( const std::string& value );
                virtual XmlNodeType getNodeType ( void ) const;
        };
};
#endif// MI_XML_ATTRIBUTE_HPP
