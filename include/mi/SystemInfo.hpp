#ifndef MI_SYSTEM_INFO_HPP
#define MI_SYSTEM_INFO_HPP 1
#include <string>
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

        class SystemInfo
        {
        public:
                static std::string getCpuName ( void );
                static double      getMemorySize ( void );
                static int         getNumCores ( void );
                static std::string getDate ( void );
                static double      getPeakMemorySize ( const SIZE_TYPE type = MI_MEGA_BYTE );
                static void print ( std::ostream&  out );
        private:
                // only for unix-like system
                static std::string get_sysctl        ( const std::string&  key );
                static double      get_sysctl_double ( const std::string&  key );
                static int         get_sysctl_int    ( const std::string&  key );
        };
}
#endif// MI_SYSTEM_INFO_HPP
