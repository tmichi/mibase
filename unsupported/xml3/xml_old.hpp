#ifndef MI_XML_HPP
#define MI_XML_HPP 1
#include <list>
#include <map>
#include <string>
#include <sstream>
#include <memory>
#include <iomanip>
#include <mi/Exporter.hpp>
namespace mi
{
        enum XmlNodeType {
                InvalidNode,
                ElementNode,
                TextNode
        };

        class XmlNode
        {
        private:
                void operator=( const XmlNode& node );
                XmlNode( const XmlNode& node );
        protected:
                XmlNode ( void )
                {
                        return;
                }
        public:
                virtual ~XmlNode ( void )
                {
                        return;
                }

                virtual XmlNodeType getType ( void ) const
                {
                        return InvalidNode;
                }

                virtual bool isLeaf( void ) const = 0;
        };

        class XmlElement : public XmlNode
        {
        public:
                XmlElement ( const std::string &name ) : XmlNode(), _name( name )
                {
                        this->_children.clear();
                        this->_attributes.clear();
                        return;
                }

                ~XmlElement ( void )
                {
                        return;
                }

                virtual XmlNodeType getType ( void ) const
                {
                        return ElementNode;
                }

                virtual bool isLeaf( void ) const
                {
                        return this->_children.size() == 0;
                }

                void addChild ( std::shared_ptr<XmlNode> node )
                {
                        this->_children.push_back( node );
                }

                void addAttribute ( const std::string& key, const std::string& value = std::string() )
                {
                        this->_attributes[key] = value;
                }

                std::list< std::shared_ptr<XmlNode> >& getChildren( void )
                {
                        return this->_children;
                }

                const std::map<std::string, std::string>& getAttributes( void ) const
                {
                        return this->_attributes;
                };

                std::string getAttribute( const std::string& key ) const
                {
                        std::map<std::string, std::string>::const_iterator iter = this->_attributes.find( key );
                        if ( iter != this->_attributes.end() ) return iter->second;
                        else return std::string(); // if key does not exist
                }

                std::list<std::string> getAttributeKeys( void ) const
                {
                        std::list<std::string> keys;
                        const std::map<std::string, std::string>& attr = this->_attributes;

                        for ( std::map<std::string, std::string>::const_iterator iter = attr.begin() ; iter != attr.end() ; ++iter ) {
                                keys.push_back( iter->first );
                        }
                        return keys;
                }

                const std::string& getName ( void ) const
                {
                        return this->_name;
                }
        private:
                std::string _name;
                std::list<std::shared_ptr<XmlNode> > _children;
                std::map<std::string, std::string> _attributes;
        };

        class XmlText : public XmlNode
        {
        public:
                XmlText ( void ) : XmlNode(), _text ( std::string() )
                {
                        return;
                }

                ~XmlText ( void )
                {
                        return;
                }

                XmlNodeType getType  ( void ) const
                {
                        return TextNode;
                }

                bool isLeaf ( void ) const
                {
                        return true;
                }

                void setText ( const std::string& text )
                {
                        this->_text = text;
                }

                const std::string& getText ( void ) const
                {
                        return this->_text;
                }

        private:
                std::string _text;
        };

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

};
#endif// MI_XML_HPP


