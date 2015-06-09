ADD_LIBRARY( mibase SHARED 
	     Argument.cpp
	     Attribute.cpp
AttributeSet.cpp
BooleanAttribute.cpp
CommandTemplate.cpp
DoubleNumericAttribute.cpp
Exporter.cpp
FileNameConverter.cpp
Importer.cpp
NumericAttribute.cpp
#ParallelFor.cpp
Parse.cpp
Progress.cpp
StringAttribute.cpp
SystemInfo.cpp
Thread.cpp
Timer.cpp
Tokenizer.cpp
TripleNumericAttribute.cpp
			 )
SET_TARGET_PROPERTIES(mibase PROPERTIES VERSION ${serial} SOVERSION ${soserial})
INSTALL(TARGETS mibase LIBRARY DESTINATION lib)


