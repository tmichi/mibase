#include <mi/XmlText.hpp>
namespace mi
{
        class XmlText::Impl
        {
	private:
                std::string _text; 
        public:
		Impl ( void )
                {
                        return;
                }
                ~Impl ( void )
                {
                        return;
                }

		const std::string& getText( void ) const {
			return this->_text;
		}
		
		void setText ( const std::string& str ) {
			this->_text = str;
			return ;
		}
        };
        XmlText::XmlText ( void ) : XmlNode(), _impl ( new Impl )
        {
                return;
        }

        XmlText::~XmlText ( void )
        {
                delete this->_impl;
                return;
        }

        XmlNodeType
        XmlText::getType  ( void ) const
        {
                return TextNode;
        }

        bool
        XmlText::isLeaf ( void ) const
        {
                return true;
        }

        void
        XmlText::setText ( const std::string& text )
        {
                this->_impl->setText(text);
        }

        const std::string&
        XmlText::getText ( void ) const
        {
                return this->_impl->getText();
        }
}


