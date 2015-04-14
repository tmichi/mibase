/**
 * @file Parse.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_PARSE_HPP
#define MI_PARSE_HPP 1

#include <string>
#include <cstdlib>
namespace mi
{
        /**
         * @brief Convert string to other types.
         * @param [in] value String.
         * @return Conveted value.
         */
        template<typename T>
        T parse ( const std::string& value );
}//namespace mi
#endif// MI_PARSE_HPP
