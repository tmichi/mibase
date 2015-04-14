/**
 * @file Limits.hpp
 * @author Takashi Michikawa
 */
#ifndef MI_LIMITS_HPP
#define MI_LIMITS_HPP 1
#include <limits>
#ifdef min
#undef min
#undef max
#endif
namespace mi
{
        template<typename T> inline T min_value ( void )
        {
                return std::numeric_limits<T>::min();
        }
        template<typename T> inline T max_value ( void )
        {
                return std::numeric_limits<T>::max();
        }
};
#endif// MI_LIMITS_HPP

