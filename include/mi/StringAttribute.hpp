/**
 * @file StringAttribute.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#pragma once
#ifndef MI_STRING_ATTRIBUTE_HPP
#define MI_STRING_ATTRIBUTE_HPP 1
#include "Attribute.hpp"
namespace mi
{
        /**
         * @class StringAttribute StringAttribute.hpp <mi/StringAttribute.hpp>
         * @brief Manage string type attributes.
         */
        class StringAttribute : public Attribute
        {
        public:
                /**
                 * @brief Constructor.
                 * @param [in] key Key.
                 * @param [in] value Value.
                 */
                explicit StringAttribute ( const std::string& key,  std::string& value );

                /**
                 * @brief Destructor.
                 */
                ~StringAttribute ( void );

                /**
                 * @brief Parse the argument.
                 * @param [in] arg Argument.
                 * @retval true Success.
                 * @retval false Failure.
                 */
                bool parse ( const Argument& arg );
                /**
                 * @brief Set default value.
                 * @return A reference to the object.
                 */
                StringAttribute&  setDefaultValue ( const std::string& defaultValue ) ;

                /**
                 * @brief Set this attribute is mandatory.
                 * @return A reference to the object.
                 */
                StringAttribute& setMandatory ( void );
                StringAttribute& setHidden ( void );
                StringAttribute& setMessage ( const std::string& message );

                /**
                 * @brief Get string value.
                 * @return String value.
                 */
                std::string toString ( void ) const ;
                std::string getValue ( void ) const ;
        private:
                class Impl;
                Impl* _impl;
        };
};
#endif// MI_STRING_ATTRIBUTE_HPP

