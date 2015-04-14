/**
 * @file DoubleNumericAttribute.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#pragma once
#ifndef MI_DOUBLE_NUMERIC_ATTRIBUTE_HPP
#define MI_DOUBLE_NUMERIC_ATTRIBUTE_HPP 1
#include "NumericAttribute.hpp"
namespace mi
{
        class AttributeSet;
        /**
         * @class DoubleNumericAttribute  DoubleNumericAttribute.hpp <mi/DoubleNumericAttribute.hpp>
         * @brief Attribute for DoubleNumeric object.
         */
        template <typename T>
        class DoubleNumericAttribute : public Attribute
        {
        public:
                explicit DoubleNumericAttribute ( const std::string& key,  NumericAttribute<T>* attr0,  NumericAttribute<T>* attr1 );
                ~DoubleNumericAttribute ( void );
                /**
                 * @brief Analyze all of childattributes.
                 * @retval true Success.
                 * @retval false Failure. Call AttributeSet::printError() to check which attribute is failed.
                 */
                bool parse ( const Argument& arg );
                /**
                 * @brief Print error messages on console.
                 */
                void printError ( void );

                /**
                 * @brief Set minimum value.
                 * @param [in] minValue Minimum value.
                 * @return Itself.
                 */
                DoubleNumericAttribute<T>&  setMin ( const T min0, const T min1 ) ;

                /**
                 * @brief Set maximum value.
                 * @param [in] maxValue Maximum value.
                 * @return Itself.
                 */
                DoubleNumericAttribute<T>& setMax ( const T max0, const T max1 ) ;

                /**
                 * @brief Set minimum / maximum value.
                 * @param [in] minValue Minimum value.
                 * @param [in] maxValue Maximum value.
                 * @return Itself.
                 */
                DoubleNumericAttribute<T>& setMinMax (  const T min0, const T min1, const T max0, const T max1 ) ;

                /**
                 * @brief Set default value.
                 * @param [in] defaultValue Default value.
                 * @return Itself.
                 */
                DoubleNumericAttribute<T>&  setDefaultValue ( const T default0, const T default1 );

                /**
                 * @brief Set this attribute must be within a range.
                 * @return Itself.
                 */
                DoubleNumericAttribute<T>& setOutRangeRejected ( void ) ;

                /**
                 * @brief Get value.
                 * @return Value.
                 */
                std::string toString ( void ) const ;
                std::string getValue ( void ) const ;

                /**
                 * @brief Set this attribute is mandatory.
                 * @return Itself.
                 */
                DoubleNumericAttribute<T>& setMandatory ( void ) ;
                DoubleNumericAttribute<T>& setHidden ( void ) ;
                DoubleNumericAttribute<T>& setMessage ( const std::string& message ) ;
        private:
                NumericAttribute<T>* _attr0;
                NumericAttribute<T>* _attr1;
        };
}
#endif// MI_DOUBLE_NUMERIC_ATTRIBUTE_HPP
