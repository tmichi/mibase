/**
 * @file Clamp.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_CLAMP_HPP
#define MI_CLAMP_HPP 1
//Undefine min / max macro if they exist.
#ifdef min
#undef min
#undef max
#endif
namespace mi
{
        /**
         * @brief Return smaller value.
         * @param[in] a Value.
         * @param[in] b Value.
         * @retval a if a < b.
         * @retval b otherwise.
         */
        template <typename T>
        inline const T min ( const T a, const T b )
        {
                return ( a < b ) ? a : b ;
        };

        /**
         * @brief Return larger value.
         * @param[in] a Value.
         * @param[in] b Value.
         * @retval a if a > b.
         * @retval b otherwise.
         */
        template <typename T>
        inline const T max ( const T a, const T b )
        {
                return ( b < a ) ? a : b ;
        }

        /**
         * @brief Return smaller value.
         * @param[in] val Value.
         * @param[in] vmin Lower value.
         * @param[in] vmax Upper value.
         * @retval val  if vmin <= val <= vmax.
         * @retval vmin if val < vmin
         * @retval vmax  otherwise.
         */
        template <typename T>
        inline const T clamp ( const T val, const T vmin , const T vmax )
        {
                return mi::min ( mi::max ( val, vmin ) , vmax );
        }
}

#endif// MI_CLAMP_HPP
