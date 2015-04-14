/**
 * @file BooleanAttribute.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#pragma once
#ifndef MI_BOOLEAN_ATTRIBUTE_HPP
#define MI_BOOLEAN_ATTRIBUTE_HPP 1
#include "Attribute.hpp"

namespace mi
{
        /**
         * @class BooleanAttribute BooleanAttribute.hpp "BooleanAttribute.hpp"
         * @brief Attribute for boolean object.
         *
         * @code
         * bool isDebug;
         * mi::AttributeSet attrSet;
         * attrSet.setBooleanAttribute("--debug", isDebug);
         * @endcode
         */
        class BooleanAttribute : public Attribute
        {
        public:
                /**
                 * @brief Constructor.
                 * @param [in] key Key.
                 * @param [in] value Value.
                 */
                explicit BooleanAttribute ( const std::string& key,  bool& value );
                /**
                 * @brief Analyze the attribute.
                 * @param [in] arg Argument object.
                 * @retval true This method always returns true.
                 */
                bool parse ( const Argument& arg );
                /**
                 * @brief Returns value.
                 * @return Return "off" when the key is not found and "on" when the key is found.
                 */
                std::string toString ( void ) const;
                std::string getValue ( void ) const;
                BooleanAttribute& setMessage ( const std::string& message );
        private:
                bool&    _value; ///< Value.
        }; //class BooleanAttribute
}//namespace mi
#endif // MI_BOOLEAN_ATTRIBUTE_HPP
