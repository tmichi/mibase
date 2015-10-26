#include "XmlNode.hpp"
#include "XmlElement.hpp"
#include "XmlDocument.hpp"
#include "XmlText.hpp"
#include "XmlDocumentExporter.hpp"
#include <iostream>
int main ( int argc, char** argv )
{
        mi::XmlDocument* doc = new mi::XmlDocument();
        mi::XmlElement *elem0 = new mi::XmlElement( "hoge" );
        doc->appendChild( elem0 );
        mi::XmlElement *elem1 = new mi::XmlElement( "hage" );
        elem0->appendChild( elem1 );
        elem0->setAttribute( "test", "30" );
        mi::XmlText* elem2 = new mi::XmlText();
        elem2->setData( "hoge1" );
        elem1->appendChild( elem2 );
        mi::XmlElement *elem3 = new mi::XmlElement( "hyge" );
        elem0->appendChild( elem3 );
        mi::XmlDocumentExporter exporter( doc );
        exporter.write( "test.xml" );
        delete doc;
        return 0;
}

