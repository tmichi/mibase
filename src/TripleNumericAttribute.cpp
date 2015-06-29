/**
 * @file TripleNumericAttribute.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/TripleNumericAttribute.hpp>
#include <sstream>
namespace mi
{
        template<typename T>
        TripleNumericAttribute<T>::TripleNumericAttribute ( const std::string& key,  NumericAttribute<T>* attr0,  NumericAttribute<T>* attr1,  NumericAttribute<T>* attr2 ) : Attribute ( key )
        {
                this->_attr0 = attr0;
                this->_attr1 = attr1;
                this->_attr2 = attr2;
                return;
        }
        template<typename T>
        TripleNumericAttribute<T>::~TripleNumericAttribute ( void )
        {
                delete this->_attr0;
                delete this->_attr1;
                delete this->_attr2;
                return;
        }

        template<typename T>
        bool
        TripleNumericAttribute<T>::parse ( const Argument& arg )
        {
                bool eval0 = this->_attr0->parse ( arg );
                bool eval1 = this->_attr1->parse ( arg );
                bool eval2 = this->_attr2->parse ( arg );
                return eval0 && eval1 && eval2;
        }
        template<typename T>
        void
        TripleNumericAttribute<T>::printError ( void )
        {
                this->_attr0->printError();
                this->_attr1->printError();
                this->_attr2->printError();
                return;
        }
        template<typename T>
        TripleNumericAttribute<T>&
        TripleNumericAttribute<T>::setMin ( const T min0, const T min1, const T min2 )
        {
                this->_attr0->setMin ( min0 );
                this->_attr1->setMin ( min1 );
                this->_attr2->setMin ( min2 );
                return *this;
        }
        template<typename T>
        TripleNumericAttribute<T>&
        TripleNumericAttribute<T>::setMax ( const T max0, const T max1, const T max2 )
        {
                this->_attr0->setMax ( max0 );
                this->_attr1->setMax ( max1 );
                this->_attr2->setMax ( max2 );
                return *this;
        }
        template<typename T>
        TripleNumericAttribute<T>&
        TripleNumericAttribute<T>::setMinMax (  const T min0, const T min1, const T min2, const T max0, const T max1, const T max2 )
        {
                return this->setMin ( min0, min1, min2 ).setMax ( max0, max1, max2 );
        }

        /**
         * @brief Set default value.
         * @param [in] defaultValue Default value.
         * @return Itself.
         */
        template<typename T>
        TripleNumericAttribute<T>&
        TripleNumericAttribute<T>::setDefaultValue ( const T default0, const T default1, const T default2 )
        {
                this->_attr0->setDefaultValue ( default0 );
                this->_attr1->setDefaultValue ( default1 );
                this->_attr2->setDefaultValue ( default2 );
                return *this;
        }

        /**
         * @brief Set this attribute must be within a range.
         * @return Itself.
         */
        template<typename T>
        TripleNumericAttribute<T>&
        TripleNumericAttribute<T>::setOutRangeRejected ( void )
        {
                this->_attr0->setOutRangeRejected();
                this->_attr1->setOutRangeRejected();
                this->_attr2->setOutRangeRejected();
                return *this;
        }

        /**
         * @brief Get value.
         * @return Value.
         */
        template<typename T>
        std::string
        TripleNumericAttribute<T>::toString ( void ) const
        {
                std::stringstream ss;
                ss << this->getKey() << " : " << this->getValue();
                return ss.str();
        }

        template<typename T>
        std::string
        TripleNumericAttribute<T>::getValue ( void ) const
        {
                std::stringstream ss;
                ss << this->_attr0->getValue() << " ";
                ss << this->_attr1->getValue() << " ";
                ss << this->_attr2->getValue();
                return ss.str();
        }
        template<typename T>
        TripleNumericAttribute<T>&
        TripleNumericAttribute<T>::setMandatory ( void )
        {
                this->_attr0->setMandatory();
                this->_attr1->setMandatory();
                this->_attr2->setMandatory();
                return *this;
        }
        template<typename T>
        TripleNumericAttribute<T>&
        TripleNumericAttribute<T>::setHidden ( void )
        {
                Attribute::setHidden();
                return *this;
        }
        template<typename T>
        TripleNumericAttribute<T>&
        TripleNumericAttribute<T>::setMessage ( const std::string& message )
        {
                Attribute::setMessage ( message ) ;
                return *this;
        }

        template class TripleNumericAttribute<unsigned char>;
        template class TripleNumericAttribute<char>;
        template class TripleNumericAttribute<unsigned short>;
        template class TripleNumericAttribute<short>;
        template class TripleNumericAttribute<unsigned int>;
        template class TripleNumericAttribute<int>;
        template class TripleNumericAttribute<float>;
        template class TripleNumericAttribute<double>;
}

