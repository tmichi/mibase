/**
 * @file Argument.hpp
 * @brief Class declaration of mi::Argument
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#pragma once
#ifndef MI_ARGUMENT_HPP
#define MI_ARGUMENT_HPP 1

#include <string>
#include <iostream>

namespace mi
{
        /**
         * @class Argument Argument.hpp <mi/Argument.hpp>
         * @brief Argument object.
         *
         * @sa AttributeSet, NumericAttribute, BooleanAttribute, StringAttribute
         */
        class Argument
        {
        private:
                // prevent copy constructor and = operator.
                Argument ( const Argument& that );
                void operator = ( const Argument& that );
        public:
                /**
                 * @brief Constructor.
                 * @param [in] argc The number of argv strings. This corresponds to argc in main().
                 * @param [in] argv Argument strings. This corresponds to argv in main().
                 */
                explicit Argument ( int argc = 0 , char** argv = NULL );

                /**
                 * @brief Destructor.
                 */
                ~Argument ( void );

                /**
                 * @brief Get size of argument array.
                 * @return The number of arguments.
                 */
                int size ( void ) const;

                /**
                 * @brief Add argument string.
                 * @param [in] str Arguments ( not parsed.)
                 * @return Argument object.
                 */
                Argument& add ( const std::string& str );

                /**
                 * @brief Check the key exists or not.
                 * @param [in] key Key.
                 * @param [in] offset Offset value.
                 * @retval true The key exists.
                 * @retval false The key does not exist.
                 */
                bool exist ( const std::string& key, const int offset = 0 ) const;

                /**
                 * @brief Get value associated with the key.
                 * @param [in] key Key.
                 * @param [in] offset Offset value.
                 * @return Value associated with the key. return 0 if the key does not exist.
                 */
                template <typename T>
                T get ( const std::string& key, const int offset = 1 ) const;

                /**
                 * @brief Get value at i-th argument.
                 * @param [in] idx Index.
                 * @return i-th argument. return 0 when the index is invalid.
                 */
                template <typename T>
                T get ( const int idx ) const ;

                /**
                 *  @brief Find index of the key.
                 *  @param [in] key Key.
                 *  @param [in] offset Offset value.
                 *  @return Index of the value. Return -1 when offset value is invalid or the key does not exist.
                 */
                int find ( const std::string& key, const int offset = 0 ) const;

                /**
                 * @brief Print arguments.
                 * @param [in] out output stream.
                 */
                void print ( std::ostream& out );
        private:
                class Impl;
                Argument::Impl* _impl;
        };
} //namespace mi
#endif //MI_ARGUMENT_HPP
