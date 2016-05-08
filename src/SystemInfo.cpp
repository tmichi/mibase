#include <mi/SystemInfo.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <sstream>

#include "SystemInfoInternal.hpp"

namespace mi
{
        std::string
        SystemInfo::getCpuName ( void )
        {
                return mi::internal::SystemInfoInternal::getInstance().getCpuName();
        }

        double
        SystemInfo::getMemorySize ( void )
        {
                return mi::internal::SystemInfoInternal::getInstance().getMemorySize();
        }

        int
        SystemInfo::getNumCores ( void )
        {
                return mi::internal::SystemInfoInternal::getInstance().getNumCores();
        }

        std::string
        SystemInfo::getDate ( void )
        {
                return mi::internal::SystemInfoInternal::getInstance().getDate();
        }
        void
        SystemInfo::print ( std::ostream&  out )
        {
                out << "date: "  << SystemInfo::getDate()       << std::endl;
                out << "cpu: "   << SystemInfo::getCpuName()    << "(" << SystemInfo::getNumCores() << "cores)" << std::endl;
                out << "memory:" << SystemInfo::getMemorySize() << "[gb]" << std::endl;
        }

        double
        SystemInfo::getPeakMemorySize ( const SIZE_TYPE type )
        {
                double peakMemory = mi::internal::SystemInfoInternal::getInstance().getPeakMemory();
                if ( type == MI_GIGA_BYTE ) {
                        peakMemory /= 1024 * 1024 * 1024 ;
                } else if ( type == MI_MEGA_BYTE ) {
                        peakMemory /= 1024 * 1024;
                } else if ( type == MI_KILO_BYTE ) {
                        peakMemory /= 1024;
                }
                return  peakMemory;
        }
}



