#include "xml.hpp"
#include <iostream>
using namespace mi;
int main ( int argc, char** argv ) {
	std::shared_ptr<XmlDocument> doc(new XmlDocument);
	std::shared_ptr<XmlElement>  ele(new XmlElement("node"));
	ele->addAttribute("atr", "x");
	std::shared_ptr<XmlText> txt ( new XmlText ) ;
	txt->setText("10");
	ele->addChild(std::dynamic_pointer_cast<XmlNode>(txt));
	doc->addRoot(ele);
	XmlDocumentExporter(doc, "utf-8").write("test.xml");
	return 0;
}
