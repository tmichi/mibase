#ifndef MI_XML_HPP
#define MI_XML_HPP 1
#include <list>
#include <map>
#include <string>
#include <sstream>
namespace mi {
	enum XmlNodeType {
		InvalidNode,
		ElementNode, 
		TextNode
	};
	
	class XmlNode {
	private:
		void operator=( const XmlNode& node);
		XmlNode( const XmlNode& node);
	public:
		
		XmlNode ( void ) {
			return;
		}

		virtual ~XmlNode  ( void ) {
			return;
		}

		virtual XmlNodeType getType ( void ) const {
			return InvalidNode;
		}
		
		virtual bool isLeaf( void ) const = 0;
		virtual std::string getValue( void ) const = 0;
		virtual std::string toString( void ) const = 0;
	};

	class XmlElement : public XmlNode {
	public:
		XmlElement ( const std::string &name) :XmlNode(), _name(name) {
			this->_children.clear();
			this->_attributes.clear();
			return;
		}
		~XmlElement ( void ) {
			return;
		}
		virtual XmlNodeType getType ( void ) const {
			return ElementNode;
		}
		
		void addChild ( XmlNode* node ) {
			this->_children.push_back(node);
		}

		void addAttribute ( const std::string key, const std::string value = std::string()) {
			this->_attributes[key] = value;
		}

		std::list<XmlNode*>& getChildren(void) {
			return this->_children;
		}


		std::string getAttribute( const std::string& key ) const {
			std::map<std::string, std::string>::const_iterator iter = this->_attributes.find(key);
			if ( iter != this->_attributes.end()) return iter->second;
			else return std::string(); // if key does not exist
		}

		int getAttributeKeys( std::list<std::string>& keys ) {
			std::map<std::string, std::string>& attr = this->_attributes;
			std::map<std::string, std::string>::iterator iter;
			for ( iter = attr.begin() ; iter != attr.end() ; ++iter ) {
				keys.push_back(iter->first);
			}
			return keys.size();
		}
		
		std::string getName ( void ) const {
			return this->_name;
		}

		std::string getValue ( void ) const {
			std::stringstream ss;
			std::list<XmlNode*>::const_iterator begin = this->_children.begin();
			std::list<XmlNode*>::const_iterator end = this->_children.end();
			for ( std::list<XmlNode*>::const_iterator iter = begin ; iter != end ; ++iter ) {
				ss<<(*iter)->toString();
			}	
			return ss.str();
		}
		
		std::string toString ( void ) const {
			std::stringstream ss;
			if ( this->isLeaf() ) ss<<this->to_string_element_leaf();
			else {
				ss<<this->to_string_element_open();
				ss<<this->getValue();				
				ss<<this->to_string_element_close();
			}
			return ss.str();
		}
		virtual bool isLeaf( void ) const {
			return this->_children.size() == 0;
		}
	private:
		std::string to_string_attribute( void ) const {
			std::stringstream ss;

			const std::map<std::string, std::string>& attr = this->_attributes;
			std::map<std::string, std::string>::const_iterator iter;
			for ( iter = attr.begin() ; iter != attr.end() ; ++iter ) {
				ss<<iter->first<<"=\""<<iter->second<<"\" ";
			}

			ss<<"\b";
			return ss.str();
		}
		std::string to_string_element_open( void) const  {
			std::stringstream ss;
			ss<<"<"<<this->getName()<<" ";
			ss<<this->to_string_attribute();
			ss<<">"<<std::endl;
			return ss.str();
		}
		
		std::string to_string_element_close( void) const {
			std::stringstream ss;
			ss<<std::endl;
			ss<<"</"<<this->getName()<<">";
			return ss.str();
		}
		
		std::string to_string_element_leaf ( void) const {
			std::stringstream ss;
			ss<<"<"<<this->getName()<<" ";
			ss<<this->to_string_attribute();
			ss<<"/>"<<std::endl;
			return ss.str();
		}
	private:
		std::string _name;
		std::list<XmlNode*> _children;
		std::map<std::string, std::string> _attributes;
	};
	
	class XmlText : public XmlNode {
	public:
		XmlText ( void ) : XmlNode(), _text (std::string()) {
			return;
		}
		
		~XmlText ( void ) {
			return;
		}
		
		void setText ( const std::string& text ) {
			this->_text = text;
		}
		
		XmlNodeType getType  ( void ) const {
			return TextNode;
		}
		std::string getValue ( void ) const {
			return this->_text;
		}
		std::string toString ( void ) const {
			return this->getValue();
		}
		virtual bool isLeaf ( void ) const {
			return true;
		}
	private:
		std::string _text;
	};
	
	class XmlDocument{
	public:
		XmlDocument ( void ) {
			this->_element = NULL;
		}
		~XmlDocument ( void ) {
			return;
		}
		void addRoot(XmlElement* element) {
			this->_element = element;
		}
		XmlElement* getRoot( void ) {
			return this->_element;
		}
		std::string toString ( void ) const  {
			return this->_element->toString();
		}
	private:
		XmlElement* _element;
	};
};
#endif// MI_XML_HPP

