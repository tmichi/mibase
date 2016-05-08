#include <mi/XmlElement.hpp>

namespace mi
{
        XmlElement::XmlElement ( const std::string& name ) : XmlNode(), _name ( name )
        {
                this->_children.clear();
                this->_attributes.clear();
                return;
        }

        XmlElement::~XmlElement ( void )
        {
                return;
        }

        XmlNodeType
        XmlElement::getType ( void ) const
        {
                return ElementNode;
        }

        bool
        XmlElement::isLeaf ( void ) const
        {
                return this->_children.size() == 0;
        }

        void
        XmlElement::addChild ( std::shared_ptr<XmlNode> node )
        {
                this->_children.push_back ( node );
        }

        void
        XmlElement::addAttribute ( const std::string& key, const std::string& value )
        {
                this->_attributes[key] = value;
        }

        std::list< std::shared_ptr<XmlNode> >&
        XmlElement::getChildren ( void )
        {
                return this->_children;
        }

        const std::map<std::string, std::string>&
        XmlElement::getAttributes ( void ) const
        {
                return this->_attributes;
        };

        std::string
        XmlElement::getAttribute ( const std::string& key ) const
        {
                std::map<std::string, std::string>::const_iterator iter = this->_attributes.find ( key );

                if ( iter != this->_attributes.end() ) {
                        return iter->second;
                } else {
                        return std::string();        // if key does not exist
                }
        }

        std::list<std::string>
        XmlElement::getAttributeKeys ( void ) const
        {
                std::list<std::string> keys;
                const std::map<std::string, std::string>& attr = this->_attributes;

                for ( std::map<std::string, std::string>::const_iterator iter = attr.begin() ; iter != attr.end() ; ++iter ) {
                        keys.push_back ( iter->first );
                }

                return keys;
        }

        const std::string&
        XmlElement::getName ( void ) const
        {
                return this->_name;
        }

}



