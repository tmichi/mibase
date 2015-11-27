#ifndef MI_XML_DOCUMENT_HPP
#define MI_XML_DOCUMENT_HPP 1

#include <list>
#include <map>
#include <string>
#include <sstream>
#include <memory>
#include <iomanip>
#include <mi/Exporter.hpp>
namespace mi
{
        class XmlDocument
        {
        public:
                XmlDocument ( void )
                {
                        return;
                }
                ~XmlDocument ( void )
                {
                        return;
                }
                void addRoot( std::shared_ptr<XmlElement> element )
                {
                        this->_element = element;
                }
                std::shared_ptr<XmlElement> getRoot( void )
                {
                        return this->_element;
                }
        private:
                std::shared_ptr<XmlElement> _element;
        };
}
#endif// MI_XML_DOCUMENT_HPP


