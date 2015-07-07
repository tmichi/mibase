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
             StringAttribute.cpp
             SystemInfo.cpp
	     TestSuite.cpp
	     TestCase.cpp
             Thread.cpp
             Timer.cpp
             Tokenizer.cpp
             TripleNumericAttribute.cpp
           )
SET_TARGET_PROPERTIES( mibase PROPERTIES 
			VERSION ${serial} SOVERSION ${soserial}
			 )
