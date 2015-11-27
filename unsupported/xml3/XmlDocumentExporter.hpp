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
                std::shared_ptr<XmlDocument> _xmlDocument;
                std::string _encoding;
        public:
                XmlDocumentExporter( std::shared_ptr<XmlDocument> xmlDocument, const std::string encoding = "UTF-8" )
                        : mi::Exporter( false ), _xmlDocument( xmlDocument ) , _encoding( encoding )
                {
                        return;
                }

                ~XmlDocumentExporter ( void )
                {
                        return;
                }
        private:
                bool writeHeader ( std::ofstream& fout )
                {
                        fout << "<?xml version=\"1.0\" encoding=\"" << this->_encoding << "\" ?>" << std::endl;
                        return true;
                }

                bool writeBody ( std::ofstream& fout )
                {
                        return this->write_node( fout, this->_xmlDocument->getRoot(), 0 );
                }

                bool write_node ( std::ostream& out, const std::shared_ptr<XmlNode>& node, const int indent )
                {
                        this->add_indent( out, indent );
                        if ( node->getType() == TextNode ) {
                                out << std::dynamic_pointer_cast<XmlText>( node )->getText() << std::endl;
                        } else if ( node->getType() == ElementNode ) {
                                std::shared_ptr<XmlElement> elem = std::dynamic_pointer_cast<XmlElement>( node );
                                out << "<" << elem->getName();
                                const std::map<std::string, std::string>& attr = elem->getAttributes();
                                for ( std::map<std::string, std::string>::const_iterator iter = attr.begin() ; iter != attr.end() ; ++iter ) {
                                        out << " " << iter->first << "=\"" << iter->second << "\"";
                                }
                                if ( elem->isLeaf() ) { //  <node/>
                                        out << "/>" << std::endl;
                                } else {
                                        out << ">" << std::endl; // <node>
                                        // children
                                        const std::list< std::shared_ptr<XmlNode> >& children = elem->getChildren();
                                        for ( std::list< std::shared_ptr<XmlNode> >::const_iterator iter = children.begin() ;
					      iter != children.end() ; ++iter ) {
                                                if ( !this->write_node( out, *iter, indent + 1 ) ) return false;
                                        }
                                        out << "</" << elem->getName() << ">" << std::endl; // </node>
                                }
                        } else return false;
                        return out.good();
                }
                void add_indent ( std::ostream& out, const int indent )
                {
			out << std::setw(indent * 4);
			return;
                }
                std::string toString ( void ) const
                {
                        return std::string( "XML" );
                }
        };

}
#endif// MI_XML_DOCUMENT_EXPOLORER_HPP


