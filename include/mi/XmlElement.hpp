#ifndef MI_XML_ELEMENT_HPP
#define MI_XML_ELEMENT_HPP 1
#include <string>
#include <memory>
#include <list>
#include <map>

#include "XmlNode.hpp"

namespace mi
{
        class XmlElement : public XmlNode
        {
        public:
                XmlElement ( const std::string &name );
                ~XmlElement ( void );
                virtual XmlNodeType getType ( void ) const;
                virtual bool isLeaf( void ) const;

                void addChild ( std::shared_ptr<XmlNode> node );
                void addAttribute ( const std::string& key, const std::string& value = std::string() );

                std::list< std::shared_ptr<XmlNode> >& getChildren( void );
                const std::map<std::string, std::string>& getAttributes( void ) const;
                std::string getAttribute( const std::string& key ) const;
                std::list<std::string> getAttributeKeys( void ) const;
                const std::string& getName ( void ) const;
        private:
                std::string _name; // element name
                std::list<std::shared_ptr<XmlNode> > _children; // child nodes.
                std::map<std::string, std::string> _attributes; // attributes
        };
}
#endif// MI_XML_ELEMENT_HPP


