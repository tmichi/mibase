/**
 * @file TripleNumericAttribute.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#pragma once
#ifndef MI_TRIPLE_NUMERIC_ATTRIBUTE_HPP
#define MI_TRIPLE_NUMERIC_ATTRIBUTE_HPP 1
#include "NumericAttribute.hpp"
namespace mi
{
        class AttributeSet;
        /**
         * @class TripleNumericAttribute  TripleNumericAttribute.hpp <mi/TripleNumericAttribute.hpp>
         * @brief Attribute for TripleNumeric object.
         */
        template <typename T>
        class TripleNumericAttribute : public Attribute
        {
        public:
                TripleNumericAttribute ( const std::string& key,  NumericAttribute<T>* attr0,  NumericAttribute<T>* attr1,  NumericAttribute<T>* attr2 );

                ~TripleNumericAttribute ( void );
                /**
                 * @brief Analyze all of childattributes.
                 * @retval true Success.
                 * @retval false Failure. Call AttributeSet::printError() to check which attribute is failed.
                 */
                bool parse ( const Argument& arg );
                /**
                 * @brief Print error messages on console.
                 */
                void printError ( void ) ;
                /**
                 * @brief Set minimum value.
                 * @param [in] min0 First minimum value.
                 * @param [in] min1 Second minimum value.
                 * @param [in] min2 Third minimum value.
                 * @return Itself.
                 */
                TripleNumericAttribute<T>&  setMin ( const T min0, const T min1, const T min2 );

                /**
                 * @brief Set maximum value.
                 * @param [in] max0 First maximum value.
                 * @param [in] max1 Second maximum value.
                 * @param [in] max2 Third maximum value.
                 * @return Itself.
                 */
                TripleNumericAttribute<T>& setMax ( const T max0, const T max1, const T max2 );

                /**
                 * @brief Set minimum / maximum value.
                 * @param [in] min0 First minimum value.
                 * @param [in] min1 Second minimum value.
                 * @param [in] min2 Third minimum value.
                 * @param [in] max0 First maximum value.
                 * @param [in] max1 Second maximum value.
                 * @param [in] max2 Third maximum value.
                 * @return Itself.
                 */
                TripleNumericAttribute<T>& setMinMax (  const T min0, const T min1, const T min2, const T max0, const T max1, const T max2 );

                /**
                 * @brief Set default value.
                 * @param [in] default0 First default value.
                 * @param [in] default1 Second default value.
                 * @param [in] default2 Third default value.
                 * @return Itself.
                 */
                TripleNumericAttribute<T>&  setDefaultValue ( const T default0, const T default1, const T default2 );

                /**
                 * @brief Set this attribute must be within a range.
                 * @return Itself.
                 */
                TripleNumericAttribute<T>& setOutRangeRejected ( void );

                /**
                 * @brief Get string.
                 * @return astring.
                 */
                std::string toString ( void ) const;
                /**
                 * @brief Get value.
                 * @return Value.
                 */
                std::string getValue ( void ) const;

                /**
                 * @brief Set this attribute is mandatory.
                 * @return Itself.
                 */
                TripleNumericAttribute<T>& setMandatory ( void );
                TripleNumericAttribute<T>& setHidden ( void );
                TripleNumericAttribute<T>& setMessage ( const std::string& message );
        private:
                NumericAttribute<T>* _attr0;
                NumericAttribute<T>* _attr1;
                NumericAttribute<T>* _attr2;
        };
}
#endif// MI_TRIPLE_NUMERIC_ATTRIBUTE_HPP
