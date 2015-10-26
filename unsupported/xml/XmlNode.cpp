#include "XmlNode.hpp"
#include <map>
#include <iostream>
namespace mi {
	class XmlNode::Impl {
	private:
		Impl ( const Impl& that) ;
		void operator = (const Impl& that);
	public:
		Impl ( const std::string& node_name, const std::string& node_value) : _node_name(node_name), _node_value(node_value) {
			return;
		}
		
		~Impl ( void ) {
			for ( mi::XmlNode::Iterator iter = this->_children.begin() ; iter != this->_children.end() ; ++iter ) {
				delete *iter;
			}
			this->_children.clear();
			
			this->_attributes.clear();
			return;
		}
		
		
		std::map<std::string, std::string>& attributes( void ) {
			return this->_attributes;
		}
		
		std::vector<XmlNode*>& children() {
			return this->_children;
		}
		
		std::string name( void ) const{
			return this->_node_name;
		}
		
		std::string value(void) const{
			return this->_node_value;
		}
	private:
		std::string _node_name;
		std::string _node_value;
		std::map<std::string, std::string> _attributes;
		std::vector<XmlNode*> _children;
	};
	
	XmlNode::XmlNode(const std::string& name, const std::string& value) : _impl ( new Impl ( name, value) ) {
		return;
	}
	
	XmlNode::~XmlNode ( void ) {
		if ( this->_impl != NULL) {
			delete _impl;
			this->_impl = NULL;
		}
		return;
	}
	
	XmlNode& 
	XmlNode::addNode ( const std::string& name, const std::string& value ) {
		Impl& impl = *(this->_impl);
		XmlNode* newNode = &(XmlNode::create(name, value));
		impl.children().push_back(newNode);
		return *newNode;
	}
	
	XmlNode& 
	XmlNode::addAttribute ( const std::string& name, const std::string& value) {
		Impl& impl = *(this->_impl);
		impl.attributes().insert(std::make_pair(name, value));
		return *this;
	}

	std::string 
	XmlNode::getName(void) const {
		return this->_impl->name();
	}

	std::string 
	XmlNode::getValue(void) const {
		return this->_impl->value();
	}
	
	int 
	XmlNode::getNumChildren ( void ) const {
		return static_cast<int>(this->_impl->children().size());
	}
	
	int 
	XmlNode::getNumAttributes ( void ) const {
		return static_cast<int>(this->_impl->attributes().size());
	}
	
	std::string 
	XmlNode::getAttribute(const std::string& name) const {
		Impl& impl = *(this->_impl);
		if ( impl.attributes().find(name) == impl.attributes().end()) return std::string();
		return impl.attributes()[name]; 
	}


	mi::XmlNode::AttrIterator 
	XmlNode::abegin (void) {

		return this->_impl->attributes().begin();
	}

	mi::XmlNode::AttrIterator 
	XmlNode::aend (void) {
		return this->_impl->attributes().end();
	}


	mi::XmlNode::Iterator
	XmlNode::begin(void) {
		return this->_impl->children().begin();
	}

	mi::XmlNode::Iterator
	XmlNode::end(void) {
		return this->_impl->children().end();
	}

	XmlNode& 
	XmlNode::create(const std::string& name, const std::string& value) {
		XmlNode* node = new XmlNode(name, value);
		return *node;
	}

	

/*
	int 
	XmlNode::getChildNodes( const std::string& name, std::vector<XmlNode&>& results ) {
		results.clear();
		std::vector<XmlNode&>& children = this->_impl->children();
		for ( std::vector::XmlNode&>::iterator iter = children.begin() ;  iter != children.end() ;  ++iter ) {
			if ( name.compare(iter->getName()) == 0 ) {
				results.push_back(*iter);
			}
		}
		return static_cast<int>(results.size());
	}
*/
};

