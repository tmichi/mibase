/**
 * @file NumericAttribute.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#pragma once
#ifndef MI_NUMERIC_ATTRIBUTE_HPP
#define MI_NUMERIC_ATTRIBUTE_HPP 1
#include "Attribute.hpp"
namespace mi
{
        /**
         * @class NumericAttribute  NumericAttribute.hpp "NumericAttribute.hpp"
         * @brief Attribute for numeric object.
         * @code
         * int value;
         * mi::AttributeSet attrSet;
         * attrSet.setNumericAttribute<int>("-i", value).setMandatory().setMinMax(10, 100);
         * @endcode
         */
        template <typename T>
        class NumericAttribute : public Attribute
        {
        public:
                /**
                 * @brief Constructor.
                 * @param [in] key Key.
                 * @param [in] value Numeric object.
                 * @param [in] offset Offset value.
                 */
                NumericAttribute ( const std::string& key,  T& value, const int offset = 1 );
                /**
                 * @brief Parse attribute.
                 * @param[in] arg Argument object.
                 * @retval true Success.
                 * @retval false Failure.
                 */
                bool parse ( const Argument& arg ) ;

                /**
                 * @brief Set minimum value.
                 * @param [in] minValue Minimum value.
                 * @return Itself.
                 */
                NumericAttribute<T>&  setMin ( const T minValue );
                /**
                 * @brief Set maximum value.
                 * @param [in] maxValue Maximum value.
                 * @return Itself.
                 */
                NumericAttribute<T>& setMax ( const T maxValue );

                /**
                 * @brief Set minimum / maximum value.
                 * @param [in] minValue Minimum value.
                 * @param [in] maxValue Maximum value.
                 * @return Itself.
                 */
                NumericAttribute<T>& setMinMax ( const T minValue, const T maxValue );

                /**
                 * @brief Set default value.
                 * @param [in] defaultValue Default value.
                 * @return Itself.
                 */
                NumericAttribute<T>&  setDefaultValue ( const T defaultValue );

                /**
                 * @brief Set this attribute must be within a range.
                 * @return Itself.
                 */
                NumericAttribute<T>& setOutRangeRejected ( void );
                /**
                 * @brief Get value.
                 * @return Value.
                 */
                std::string toString ( void ) const;
                std::string getValue ( void ) const;

                /**
                 * @brief Set this attribute is mandatory.
                 * @return Itself.
                 */
                NumericAttribute<T>& setMandatory ( void );
                NumericAttribute<T>& setHidden ( void );
                NumericAttribute<T>& setMessage ( const std::string& message );
        private:
                bool clamp_value ( T& value );
        private:
                class Impl;
                Impl* _impl;
        };
};
#endif// MI_NUMERIC_ATTRIBUTE_HPP
