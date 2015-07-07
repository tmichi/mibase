/**
 * @file NumericAttribute.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/NumericAttribute.hpp>
#include <sstream>
namespace mi
{
        template< typename T>
        class NumericAttribute<T>::Impl
        {
        private:
                Impl ( const Impl& that );
                void operator = ( const Impl& that ) ;
        public:
                Impl ( T& value, const int offset ) : _value ( value ), _offset ( offset ), _minValue ( T() ), _maxValue ( T() ), _defaultValue ( T() ),
                        _isMinSet ( false ), _isMaxSet ( false ), _isOutRangeRejected ( false )
                {
                        return;
                }

                ~Impl ( void )
                {
                        return;
                }

                T& getValue ( void )
                {
                        return this->_value;
                }

                int getOffset ( void ) const
                {
                        return this->_offset;
                }

                T getMinValue ( void ) const
                {
                        return this->_minValue;
                }

                void setMinValue ( const T minValue )
                {
                        this->_minValue = minValue;
                        this->_isMinSet = true;

                        if ( this->_isMaxSet ) {
                                this->swap_min_max ( this->_minValue, this->_maxValue );
                        }

                        this->clamp_value ( this->_defaultValue );
                        return;
                }

                T getMaxValue ( void ) const
                {
                        return this->_maxValue;
                }

                void setMaxValue ( const T maxValue )
                {
                        this->_maxValue = maxValue;
                        this->_isMaxSet = true;

                        if ( this->_isMinSet ) {
                                this->swap_min_max ( this->_minValue, this->_maxValue );
                        }

                        this->clamp_value ( this->_defaultValue );
                        return;
                }

                void setOutRangeRejected ( void )
                {
                        this->_isOutRangeRejected = true;
                        return;
                }

                T getDefaultValue() const
                {
                        return this->_defaultValue;
                }
                void setDefaultValue ( const T defaultValue )
                {
                        this->_defaultValue = defaultValue;
                        this->clamp_value ( this->_defaultValue );
                }

                bool clampValue ( T& value )
                {
                        return this->clamp_value ( value );
                }
        private:
                void	swap_min_max ( T& minValue, T& maxValue )
                {
                        if ( maxValue <  minValue ) {
                                const T tmp = minValue;
                                minValue = maxValue;
                                maxValue = tmp;
                        }

                        return;
                }

                bool clamp_value ( T& value )
                {
                        if ( this->_isMinSet && value < this->_minValue ) {
                                if ( this->_isOutRangeRejected ) {
                                        return false;
                                }

                                value = this->_minValue;
                        }

                        if ( this->_isMaxSet && value > this->_maxValue ) {
                                if ( this->_isOutRangeRejected ) {
                                        return false;
                                }

                                value = this->_maxValue;
                        }

                        return true;
                }
        private:
                T&    _value; ///< Value.

                int _offset; ///< Offset

                T    _minValue; ///< Minimum value.
                T    _maxValue; ///< Maximum value.
                T    _defaultValue;  ///< Default value.

                bool _isMinSet; ///< Minimum value is set.
                bool _isMaxSet; ///< Maximum value is set.
                bool _isOutRangeRejected; ///< Out rangevalue is rejected.
        };


        template<typename T>
        NumericAttribute<T>::NumericAttribute ( const std::string& key,  T& value, const int offset  )
                : Attribute ( key ), _impln ( new NumericAttribute<T>::Impl ( value, offset ) )
        {
                return;
        }

        template<typename T>
        NumericAttribute<T>::~NumericAttribute ( void )
        {
                if ( this->_impln != NULL ) {
                        delete this->_impln;
                        this->_impln = NULL;
                }

                return;
        }

        template<typename T>
        bool
        NumericAttribute<T>::parse ( const Argument& arg )
        {
                const int& offset = this->_impln->getOffset();
                const std::string key = this->getKey();
                T& value = this->_impln->getValue();

                if ( this->is_key_found ( arg, key, offset ) ) {
                        value = arg.get<T> ( key , offset );
                        return this->clamp_value ( value );
                } else {
                        if ( this->isMandatory() ) {
                                this->setErrorCode ( ATTRIBUTE_ERROR_KEY_NOT_FOUND );
                                return false;
                        } else {
                                value = this->_impln->getDefaultValue();
                                return true;
                        }
                }
        }

        template< typename T>
        NumericAttribute<T>&
        NumericAttribute<T>::setMin ( const T minValue )
        {
                this->_impln->setMinValue ( minValue ) ;
                return *this;
        }

        template <typename T>
        NumericAttribute<T>&
        NumericAttribute<T>::setMax ( const T maxValue )
        {
                this->_impln->setMaxValue ( maxValue );
                return *this;
        }

        template <typename T>
        NumericAttribute<T>&
        NumericAttribute<T>::setMinMax ( const T minValue, const T maxValue )
        {
                return this->setMin ( minValue ).setMax ( maxValue );
        }

        template <typename T>
        NumericAttribute<T>&
        NumericAttribute<T>::setDefaultValue ( const T defaultValue )
        {
                this->_impln->setDefaultValue ( defaultValue );
                return *this;
        }

        template <typename T>
        NumericAttribute<T>&
        NumericAttribute<T>::setOutRangeRejected ( void )
        {
                this->_impln->setOutRangeRejected();
                return *this;
        }

        template<typename T>
        std::string
        NumericAttribute<T>::toString ( void ) const
        {
                std::stringstream ss;
                ss << this->getKey();

                if ( this->_impln->getOffset() > 1 ) {
                        ss << "[" << this->_impln->getOffset() << "]";
                }

                ss << " : " << this->getValue();
                return ss.str();
        }
        template< typename T>
        std::string
        NumericAttribute<T>::getValue ( void ) const
        {
                std::stringstream ss;
                ss << this->_impln->getValue();
                return ss.str();
        }

        template<typename T>
        NumericAttribute<T>&
        NumericAttribute<T>::setMandatory ( void )
        {
                Attribute::setMandatory();
                return *this;
        }
        template<typename T>
        NumericAttribute<T>&
        NumericAttribute<T>::setHidden ( void )
        {
                Attribute::setHidden();
                return *this;
        }

        template<typename T>
        NumericAttribute<T>&
        NumericAttribute<T>::setMessage ( const std::string& message )
        {
                Attribute::setMessage ( message ) ;
                return *this;
        }

        template<typename T>
        bool
        NumericAttribute<T>::clamp_value ( T& value )
        {
                if ( !this->_impln->clampValue ( value ) ) {
                        this->setErrorCode ( ATTRIBUTE_ERROR_VALUE_OUT_OF_RANGE );
                        return false;
                } else {
                        return true;
                }
        }

#define CLASS__NUMERIC_ATTRIBUTE(TYPE)         template class NumericAttribute<TYPE>
        CLASS__NUMERIC_ATTRIBUTE ( unsigned char );
        CLASS__NUMERIC_ATTRIBUTE ( char );
        CLASS__NUMERIC_ATTRIBUTE ( unsigned short );
        CLASS__NUMERIC_ATTRIBUTE ( short );
        CLASS__NUMERIC_ATTRIBUTE ( unsigned int );
        CLASS__NUMERIC_ATTRIBUTE ( int );
        CLASS__NUMERIC_ATTRIBUTE ( float );
        CLASS__NUMERIC_ATTRIBUTE ( double );
};
