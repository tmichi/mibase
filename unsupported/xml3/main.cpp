#include "xml.hpp"
#include <iostream>
/*
<node atr = "x"> 
   10
</node>
*/

using namespace mi;
int main ( int argc, char** argv ) {
	XmlDocument doc;
	XmlElement ele("node");
	ele.addAttribute("atr", "x");
	XmlText txt;
	txt.setText("10");
	ele.addChild(dynamic_cast<XmlNode*>(&txt));
	doc.addRoot(&ele);
	std::cerr<<doc.toString()<<std::endl;
/*	XmlDocument* doc    = XmlDocument::create();
	XmlElement* element = XmlElement::create("node");
	XmlAttribute* attr  = XmlAttribute::create("atr", "x");
	element->addAttribute(attr);
	XmlText* textNode   = XmlTextNode::create("10");
	element->addNode(textNode);

	doc->addElement(element); 
	
	XmlExporter(*doc).setEncoding("UTF-8").write("test.xml");
*/
	return 0;
}
