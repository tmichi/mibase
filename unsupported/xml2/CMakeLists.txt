ADD_EXECUTABLE( xml2
                XmlDocumentExporter.hpp 		    XmlDocumentExporter.cpp
                XmlAttribute.hpp 		    XmlAttribute.cpp
                XmlDocument.hpp XmlDocument.cpp
                XmlText.hpp XmlText.cpp
                XmlElement.hpp XmlElement.cpp
                XmlNode.hpp XmlNode.cpp
                main.cpp )
TARGET_LINK_LIBRARIES( xml2 mibase )


