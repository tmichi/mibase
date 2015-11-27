#ifndef MI_XML_HPP
#define MI_XML_HPP 1

#include "XmlDocument.hpp"
#include "XmlNode.hpp"
#include "XmlText.hpp"
#include "XmlElement.hpp"
#include "XmlDocumentExporter.hpp"

namespace mi
{
        enum XmlNodeType {
                InvalidNode,
                ElementNode,
                TextNode
        };
}
#endif// MI_XML_HPP


