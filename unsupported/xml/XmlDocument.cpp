#include "XmlDocument.hpp"
namespace mi {
	XmlDocument::XmlDocument( const std::string& name, const std::string& value) : _root ( XmlNode::create(name, value) ) {
		this->setVersion();
		this->setEncoding();
		return;
	}
	
	XmlDocument::~XmlDocument ( void ) {
		delete &this->_root;
		return;
	}
	mi::XmlNode& 
	XmlDocument::getNode(void) {
		return this->_root;
	}
	
	void 
	XmlDocument::setVersion( const std::string version) {
		this->_version = version;
		return;
	}
	void 
	XmlDocument::setEncoding( const std::string encoding) {
		this->_encoding = encoding;
		return;
	}
		
	std::string 
	XmlDocument::getVersion ( void ) const {
		return this->_version;
	}

	std::string 
	XmlDocument::getEncoding( void ) const {
		return this->_encoding;
	}
}
