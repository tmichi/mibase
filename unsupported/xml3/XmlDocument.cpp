#include "XmlDocument.hpp"
namespace mi
{
        class XmlDocument::Impl
        {
	private:
                std::shared_ptr<XmlElement> _element;
        public:
                Impl ( void )
                {
                        return;
                }

                ~Impl( void )
                {
                        return;
                }
		
		void setRoot ( std::shared_ptr<XmlElement> element ) {
			this->_element = element;
		}

		std::shared_ptr<XmlElement> getRoot( void ) {
			return this->_element;
		}
        };

        XmlDocument::XmlDocument ( void ) : _impl ( new Impl() )
        {
                return;
        }
        XmlDocument::~XmlDocument ( void )
        {
                delete this->_impl;
                return;
        }
        void
        XmlDocument::addRoot( std::shared_ptr<XmlElement> element )
        {
                this->_impl->setRoot(element);
        }

        std::shared_ptr<XmlElement>
        XmlDocument::getRoot( void )
        {
                return this->_impl->getRoot();
        }
}



