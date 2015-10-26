#ifndef MI_XML_DOCUMENT_HPP
#define MI_XML_DOCUMENT_HPP 1
#include "XmlNode.hpp"
namespace mi
{
        class XmlDocument
        {
        private:
                XmlDocument ( const XmlDocument& that ) ;
                void operator = ( const XmlDocument& that ) ;
        public:
                explicit XmlDocument( const std::string& name, const std::string& value = std::string() );
                ~XmlDocument ( void );
                mi::XmlNode& getNode( void );
                void setVersion( const std::string version = std::string( "1.0" ) );
                void setEncoding( const std::string encoding = std::string( "UTF-8" ) );
                std::string getVersion ( void ) const;
                std::string getEncoding( void ) const;
        private:
                mi::XmlNode& _root;
                std::string _version;
                std::string _encoding;
        };
}
#endif // MI_XML_DOCUMENT_HPP
