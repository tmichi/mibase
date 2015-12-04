#ifndef MI_XML_DOCUMENT_HPP
#define MI_XML_DOCUMENT_HPP 1
#include <memory>
#include "XmlElement.hpp"
namespace mi
{
        class XmlDocument
        {
        private:
                XmlDocument ( const XmlDocument& that );
                void operator = ( const XmlDocument& that );
        public:
                XmlDocument ( void );
                ~XmlDocument ( void );
                void addRoot( std::shared_ptr<XmlElement> element );
                std::shared_ptr<XmlElement> getRoot( void );
        private:
                class Impl;
                Impl* _impl;
        };
}
#endif// MI_XML_DOCUMENT_HPP


