#ifndef MI_XML_DOCUMENT_HPP
#define MI_XML_DOCUMENT_HPP 1
#include <memory>
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
};
#endif// MI_XML_HPP


