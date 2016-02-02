ADD_LIBRARY( mibase STATIC #SHARED
             Argument.cpp
             Attribute.cpp
             AttributeSet.cpp
             BooleanAttribute.cpp
             CommandTemplate.cpp
             DoubleNumericAttribute.cpp
             Exporter.cpp
             FileLister.cpp
             FileNameConverter.cpp
             Importer.cpp
             NumericAttribute.cpp
             Parse.cpp
             Progress.cpp
	     Routine.cpp
             StringAttribute.cpp
	     SvgRenderer.cpp
             SystemInfo.cpp
	     TestSuite.cpp
	     TestCase.cpp
             Thread.cpp
             Timer.cpp
             Tokenizer.cpp
             TripleNumericAttribute.cpp
	     XmlDocument.cpp
	     XmlDocumentExporter.cpp
	     XmlNode.cpp
	     XmlText.cpp
	     XmlElement.cpp
           )
#SET_TARGET_PROPERTIES( mibase PROPERTIES 
#			VERSION ${serial} SOVERSION ${soserial}
#			 )
#INSTALL(TARGETS mibase ARCHIVE DESTINATION lib)

install(TARGETS mibase
    EXPORT mibase-export                   
    ARCHIVE	 DESTINATION lib			   
    LIBRARY        DESTINATION lib         
    INCLUDES       DESTINATION include     
    PUBLIC_HEADER  DESTINATION include/mi) 
install(EXPORT mibase-export                   
    FILE mibase-config.cmake                   
    DESTINATION share/cmake/mi/              
    EXPORT_LINK_INTERFACE_LIBRARIES)          
