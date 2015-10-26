#include "XmlText.hpp"

namespace mi
{
        XmlText::XmlText ( void ) : XmlNode(), _str( std::string() )
        {

        }
        XmlText::~XmlText ( void )
        {

        }
        void
        XmlText::setData ( const std::string& data )
        {
                this->_str = data;
        }

        std::string
        XmlText::getData ( void ) const
        {
                return this->_str;
        }

        mi::XmlNodeType
        XmlText::getNodeType ( void ) const
        {
                return mi::XmlNodeText;
        }
}
