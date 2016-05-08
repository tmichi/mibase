#ifndef MI_XML_DOCUMENT_HPP
#define MI_XML_DOCUMENT_HPP 1
#include <memory>
#include "XmlElement.hpp"
namespace mi
{
        /**
         * @class XmlDocument XmlDocument.hpp mi/XmlDocument.hpp
         * @breif XML document
         */
        class XmlDocument
        {
        private:
                XmlDocument ( const XmlDocument& that );
                void operator = ( const XmlDocument& that );
        public:
                /**
                 * @brief Constructor
                 */
                XmlDocument ( void );
                /**
                 * @brief Destructor
                 */
                ~XmlDocument ( void );
                /**
                 * @brief Add node to root
                 * @param [in] element Root element
                 */
                void addRoot ( std::shared_ptr<XmlElement> element );
                /**
                 * @brief Get root node
                 * @return Root node
                 */
                std::shared_ptr<XmlElement> getRoot ( void );
        private:
                class Impl;
                Impl* _impl;
        };
}
#endif// MI_XML_DOCUMENT_HPP


