#include "XmlDocumentExporter.hpp"
#include "XmlText.hpp"
#include "XmlNode.hpp"
#include "XmlAttribute.hpp"
namespace mi
{

        XmlDocumentExporter::XmlDocumentExporter (  XmlDocument* doc ) : mi::Exporter( false ), _doc( doc )
        {

        }

        XmlDocumentExporter::~XmlDocumentExporter( void )
        {

        }

        bool
        XmlDocumentExporter::writeHeader ( std::ofstream& fout )
        {
                fout << "<?xml"
                     << " version=\"1.0\""
                     << " encoding=\"UTF-8\"?>" << std::endl;
//                     << " version=\"" << this->_doc.getVersion() << "\""
//                     << " encoding=\"" << this->_doc.getEncoding() << "\"?>" << std::endl;
                return fout.good();
        }

        bool
        XmlDocumentExporter::writeBody ( std::ofstream& fout )
        {
                return this->write_node( fout, this->_doc->getDocumentElement(), 0 );
        }

        std::string
        XmlDocumentExporter::toString ( void ) const
        {
                return std::string( "xml document" );
        }

        bool
        XmlDocumentExporter::write_node ( std::ofstream& fout, mi::XmlNode* node, const int indent )
        {
                if ( node == NULL ) return fout.good();
                mi::XmlNodeType type = node->getNodeType();
                if ( type == mi::XmlNodeText ) {
                        this->add_indent( fout, indent );
                        fout << dynamic_cast<mi::XmlText*>( node )->getData() << std::endl;
                        return fout.good();
                } else if ( type == mi::XmlNodeElement ) {
                        const std::string tag = dynamic_cast<mi::XmlElement*>( node )->getTagName();
                        this->add_indent( fout, indent );
                        fout << "<" << tag;
                        //Attributes
                        mi::XmlNode* node0 = node->getFirstChildNode();
                        std::vector<mi::XmlNode*> attributes;
                        if ( node0 != NULL ) {
                                if ( node0->getNodeType() == mi::XmlNodeAttribute ) {
                                        attributes.push_back( node0 );
                                }
                                node0 =  node->getFirstChildNode()->getNextSiblingNode();
                                while ( node0 != NULL ) {
                                        if ( node0->getNodeType() == mi::XmlNodeAttribute ) {
                                                attributes.push_back( node0 );
                                        }
                                        node0 = node0->getNextSiblingNode();
                                }
                        }
                        for ( std::vector<mi::XmlNode*>::iterator iter = attributes.begin() ; iter != attributes.end() ; ++iter ) {
                                fout << " " << dynamic_cast<XmlAttribute*>( *iter )->getName()
                                     << " =\"" << dynamic_cast<XmlAttribute*>( *iter )->getValue() << "\"";
                        }
                        fout << ">" << std::endl;



                        node0 = node->getFirstChildNode();
                        // first child
                        if ( node0 != NULL ) {
                                if ( !this->write_node( fout,  node0,  indent + 1 ) ) return false;
                                node0 =  node->getFirstChildNode()->getNextSiblingNode();
                                while ( node0 != NULL ) {
                                        if ( !this->write_node( fout, node0, indent + 1 ) ) return false;
                                        node0 = node0->getNextSiblingNode();
                                }
                        }
                        this->add_indent( fout, indent );
                        fout << "</" << tag << ">" << std::endl;
                } else {


                }

                return fout.good();
        }
        void
        XmlDocumentExporter::add_indent ( std::ofstream& fout, const int indent )
        {
                const int ns = 4;
                for ( int i = 0 ; i < indent ; ++i ) {
                        for ( int j = 0 ; j < ns ; ++j ) {
                                fout << " ";
                        }
                }
        }
}

