/**
 * @file SystemInfo.hpp
 * @brief Implementation of mi::SystemInfo
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_SYSTEM_INFO_HPP
#define MI_SYSTEM_INFO_HPP 1
#include <string>
#include <iostream>

namespace mi
{
        /**
         * @enum SIZE_TYPE Size type.
         */
        enum SIZE_TYPE {
                MI_BYTE,      ///< Bytes.
                MI_KILO_BYTE, ///< Kilo bytes.
                MI_MEGA_BYTE, ///< Mega bytes.
                MI_GIGA_BYTE  ///< Giga bytes.
        };

        /**
         * @class SystemInfo SystemInfo.hpp <mi/SystemInfo.hpp>
         * @brief Some utility functions for getting system information.
         */
        class SystemInfo
        {
        public:
                /**
                 * @brief Get CPU name
                 * @return CPU name
                 */
                static std::string getCpuName ( void );
                /**
                 * @brief Get memory size
                 * @return Memory size (GB)
                 */
                static double      getMemorySize ( void );
                /**
                 * @brief Get  the number of cores
                 * @return The number of cores
                 */
                static int         getNumCores ( void );
                /**
                 * @brief Get date
                 * @return date
                 */
                static std::string getDate ( void );
                /**
                 * @brief Get peak memory size
                 * @param [in] type the unit of return value.
                 * @return Peak memory size
                 */
                static double      getPeakMemorySize ( const SIZE_TYPE type = MI_MEGA_BYTE );
                /**
                 * @brief Print all informatio
                 * @param[in] out Output stream
                 */
                static void print ( std::ostream&  out  = std::cout );
        };
}
#endif// MI_SYSTEM_INFO_HPP
