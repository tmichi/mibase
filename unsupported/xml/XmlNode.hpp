#ifndef MI_XML_NODE_HPP
#define MI_XML_NODE_HPP 1
#include <string>
#include <vector>
#include <map>
namespace mi {
	class XmlNode {
	public:
		typedef std::vector<XmlNode*>::iterator Iterator;
		typedef std::map<std::string, std::string>::iterator AttrIterator;
	private:
		XmlNode(const XmlNode& that);
		void operator = (const XmlNode& that);
		XmlNode(const std::string& name, const std::string& value = std::string());
	public:
		~XmlNode ( void ) ;

		XmlNode& addNode ( const std::string& name, const std::string& value ) ;
		XmlNode& addAttribute ( const std::string& name, const std::string& value);

		std::string getName( void ) const;
		std::string getValue( void ) const;
		int getNumChildren ( void ) const;
		int getNumAttributes ( void ) const;

		std::string getAttribute(const std::string& name) const;

		AttrIterator abegin (void);
		AttrIterator aend (void);

		Iterator begin (void);
		Iterator end (void);
		

		static XmlNode& create(const std::string& name, const std::string& value = std::string());
//		int getChildNodes( const std::string& name, std::vector<XmlNode&>& nodes );
	private:
		class Impl;
		Impl* _impl;
	};
};
#endif// MI_XML_NODE_HPP
