#ifndef MI_XML_DOCUMENT_EXPORTER_HPP
#define MI_XML_DOCUMENT_EXPORTER_HPP 1
#include "XmlDocument.hpp"
#include <mi/Exporter.hpp>
namespace mi
{
        class XmlDocumentExporter : public mi::Exporter
        {
        public:
                explicit XmlDocumentExporter (  XmlDocument* doc );
                ~XmlDocumentExporter( void );
        protected:
                bool writeHeader ( std::ofstream& fout );
                bool writeBody ( std::ofstream& fout );
                std::string toString ( void ) const;
        private:
                bool write_node ( std::ofstream& fout, mi::XmlNode* node, const int indent );
                void add_indent ( std::ofstream& fout, const int indent );
        private:
                XmlDocument* _doc;
        };
}
#endif// MI_XML_DOCUMENT_EXPORTER_HPP
