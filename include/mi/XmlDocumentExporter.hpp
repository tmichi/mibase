#ifndef MI_XML_DOCUMENT_EXPOLORER_HPP
#define MI_XML_DOCUMENT_EXPOLORER_HPP 1
#include <string>
#include <memory>
#include <iomanip>
#include "Exporter.hpp"
#include "XmlDocument.hpp"
namespace mi
{
        class XmlDocument;
        class XmlDocumentExporter : public mi::Exporter
        {
        public:
                /**
                 * @brief Constructor
                 * @param [in] xmlDocument XML document object
                 * @param [in] encoding Encoding of the document, however this is no-meaning.
                 */
                XmlDocumentExporter ( std::shared_ptr<XmlDocument> xmlDocument, const std::string encoding = "UTF-8" );
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
        private:
                class Impl;
		std::unique_ptr<Impl> _impl;
        };
}
#endif// MI_XML_DOCUMENT_EXPOLORER_HPP


