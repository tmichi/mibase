#ifndef MI_XML_DOCUMENT_HPP
#define MI_XML_DOCUMENT_HPP 1
#include <memory>
#include "NonCopyable.hpp"
#include "XmlElement.hpp"
namespace mi
{
        /**
         * @class XmlDocument XmlDocument.hpp mi/XmlDocument.hpp
         * @breif XML document
         */
        class XmlDocument : public NonCopyable
        {
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
                std::unique_ptr<Impl> _impl;
        };
}
#endif// MI_XML_DOCUMENT_HPP



