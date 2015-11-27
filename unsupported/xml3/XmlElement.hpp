#ifndef MI_XML_ELEMENT_HPP
#define MI_XML_ELEMENT_HPP 1
#include "xml.hpp"
#include "XmlNode.hpp"

#include <list>
#include <map>
#include <memory>
#include <string>

namespace mi
{
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
}
#endif// MI_XML_HPP


