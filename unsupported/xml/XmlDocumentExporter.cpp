#include "XmlDocumentExporter.hpp"
namespace mi {
	
	XmlDocumentExporter::XmlDocumentExporter (  XmlDocument& doc ) : mi::Exporter(false), _doc(doc){
			
		}
	XmlDocumentExporter::~XmlDocumentExporter(void ) {

		}

                bool 
		XmlDocumentExporter::writeHeader ( std::ofstream& fout ) {
			fout<<"<?xml"
			    <<" version=\""<<this->_doc.getVersion()<<"\""
			    <<" encoding=\""<<this->_doc.getEncoding()<<"\"?>"<<std::endl;
			return fout.good();
		}

                bool 
XmlDocumentExporter::writeBody ( std::ofstream& fout ) {
			return this->write_node( fout, _doc.getNode(), 0);
		}

                std::string 
XmlDocumentExporter::toString ( void ) const {
			return std::string("xml document");
		}

		bool 
XmlDocumentExporter::write_node ( std::ofstream& fout,mi::XmlNode& node, const int indent) {
			this->add_indent(fout, indent);
			fout<<"<"<<node.getName();
			// add attributes here
			for ( mi::XmlNode::AttrIterator aiter = node.abegin(); aiter != node.aend() ; ++aiter ) {
				fout<<" "<<aiter->first<<"=\""<<aiter->second<<"\" ";
			}

			// child 
			const bool isLeaf = ( node.getNumChildren() == 0 );
			const bool isEmpty = ( node.getValue().compare("") == 0);
			
			if ( isLeaf && isEmpty) fout<<"/>"<<std::endl;
			else {
				fout<<">"<<std::endl;

				// child nodes
				for ( mi::XmlNode::Iterator iter = node.begin(); iter != node.end() ; ++iter ) {
					this->write_node( fout, *(*iter), indent+1);
				}

				// value
				if ( !isEmpty) {
					this->add_indent(fout, indent+1);
					fout<<node.getValue()<<std::endl;
				}
				// closing
				this->add_indent(fout, indent);
				fout<<"</"<<node.getName()<<">"<<std::endl;
			}
			return fout.good();
		}
		void 
XmlDocumentExporter::add_indent ( std::ofstream& fout, const int indent ) {
			const int ns = 4;
			for ( int i = 0 ; i < indent ; ++i ) {
				for ( int j = 0 ; j < ns ; ++j ) {
					fout<<" ";
				}
			}
		}
}

