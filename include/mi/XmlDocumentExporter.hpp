#ifndef MI_XML_DOCUMENT_EXPOLORER_HPP
#define MI_XML_DOCUMENT_EXPOLORER_HPP 1
#include <string>
#include <memory>
#include <iomanip>

#include <mi/Exporter.hpp>
#include "XmlDocument.hpp"
namespace mi
{
        class XmlDocument;
        class XmlDocumentExporter : public mi::Exporter
        {
        private:
                class Impl;
                Impl* _impl;

        public:
                /**
                 * @brief Constructor
                 * @param [in] xmlDocument XML document object
                 * @param [in] encoding Encoding of the document
                 */
                XmlDocumentExporter( std::shared_ptr<XmlDocument> xmlDocument, const std::string encoding = "UTF-8" );
                /**
                 * @brief Destructor
                 */
                ~XmlDocumentExporter ( void );
        private:
                bool writeHeader ( std::ofstream& fout );
                bool writeBody ( std::ofstream& fout );
                std::string toString ( void ) const;
                bool write_node ( std::ostream& out, const std::shared_ptr<XmlNode>& node, const int indent );
                void add_indent ( std::ostream& out, const int indent );
        };
}
#endif// MI_XML_DOCUMENT_EXPOLORER_HPP


