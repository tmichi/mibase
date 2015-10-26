#include "XmlDocument.hpp"
#include "XmlDocumentExporter.hpp"
#include <iostream>
int main ( int argc, char** argv) {
	mi::XmlDocument doc( "node") ;
	mi::XmlNode& node = doc.getNode();
	node.addNode("hoge", "1");
	node.addAttribute("attr", "yes");
	mi::XmlDocumentExporter exporter(doc);
	exporter.write("test.xml");
	return 0;
}

/*
//
mi::XmlDocument& doc = mi::XmlDocumentBuilder.newDocument();
mi::XmlElement& root = doc.newElement("svg");
root.setAttribute("xmlns", "http://www.w3.org/2000/svg");
root.setAttribute("xmlns:xlink", "http://www.w3.org/1999/xlink");
root.setAttribute("width", "300");
root.setAttribute("height", "300");
doc.appendChild(root);

mi::XmlElement& line0 = root.appendChild("line");
line0.addAttribute("x1", "37.5");
line0.addAttribute("y1", "262.5");
line0.addAttribute("x2", "37.5");
line0.addAttribute("y2", "37.5");
line0.addAttribute("stroke-width", "1");
line0.addAttribute("stroke", "green");
doc.appendChild(line0);

XmlDocumentExporter::write (doc, "test.xml");


*/



