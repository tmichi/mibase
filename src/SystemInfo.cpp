#include <mi/SystemInfo.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <sstream>
//macros
//http://d.hatena.ne.jp/torutk/20090420/p1
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)// Win32 API
#ifndef	OS_WINDOWS
#define	OS_WINDOWS 1
#endif	//OS_WINDOWS
#else
#ifndef OS_UNIX
#define OS_UNIX 1
#endif//OS_UNIX
#if defined (__APPLE__)
#ifndef OS_MAC
#define OS_MAC 1
#endif//OS_MAC
#elif defined(__linux__)
#ifndef OS_LINUX
#define OS_LINUX 1
#endif//OS_LINUX
#else
#ifndef OS_UNKNOWN
#define OS_UNKNOWN 1
#endif//OS_UNKNOWN
#endif//if defined __APPLE__ __linux
#endif//if defined 

#if defined OS_WINDOWS 
#include <windows.h>
#include <process.h>
#include <intrin.h>
#include <Psapi.h>
#pragma comment(lib, "psapi.lib")
#else
#include <ctime>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/resource.h>
#endif//

namespace mi
{
	namespace sys {
#ifdef OS_WINDOWS
		std::string get_cpu_name ( void ) {
			char CPUString[0x20];
			char CPUBrandString[0x40];
			int CPUInfo[4] = { -1};
			__cpuid ( CPUInfo, 0 );
			unsigned int nIds = CPUInfo[0];
			memset ( CPUString, 0, sizeof ( CPUString ) );
			* ( ( int* ) CPUString ) = CPUInfo[1];
			* ( ( int* ) ( CPUString + 4 ) ) = CPUInfo[3];
			* ( ( int* ) ( CPUString + 8 ) ) = CPUInfo[2];
			// Calling __cpuid with 0x80000000 as the InfoType argument
			// gets the number of valid extended IDs.
			__cpuid ( CPUInfo, 0x80000000 );
			unsigned int nExIds = CPUInfo[0];
			memset ( CPUBrandString, 0, sizeof ( CPUBrandString ) );
			
			// Get the information associated with each extended ID.
			for ( unsigned int i = 0x80000000; i <= nExIds; ++i ) {
				__cpuid ( CPUInfo, i );
				
				// Interpret CPU brand string and cache information.
				if  ( i == 0x80000002 ) {
					memcpy ( CPUBrandString, CPUInfo, sizeof ( CPUInfo ) );
				} else if  ( i == 0x80000003 ) {
					memcpy ( CPUBrandString + 16, CPUInfo, sizeof ( CPUInfo ) );
				} else if  ( i == 0x80000004 ) {
					memcpy ( CPUBrandString + 32, CPUInfo, sizeof ( CPUInfo ) );
				}
			}
			std::string name;
			
			if  ( nExIds >= 0x80000004 ) {
				name = std::string ( CPUBrandString );
			}
			
			return name;
		}
		
		double get_memory_size() {
			MEMORYSTATUSEX stat;
			stat.dwLength = sizeof ( MEMORYSTATUSEX );
			
			if ( GlobalMemoryStatusEx ( &stat ) == 0 ) {
				std::cerr << "error while calling GlobalMemoryStatusEx()" << std::endl;
				return 0;
			}
			
			/// @note The retrun value is somewhat smaller than actual size.
			return static_cast<double> ( stat.ullTotalPhys / 1024.0 / 1024 / 1024 ) ;
		}

		int get_num_cores(){
			SYSTEM_INFO sysinfo;
			GetSystemInfo ( &sysinfo );
			return static_cast<int> ( sysinfo.dwNumberOfProcessors );
		}
		
		std::string get_date() {
			SYSTEMTIME systime;
			GetLocalTime ( &systime );
			std::stringstream ss;
			ss << systime.wYear << "-" << std::setw ( 2 ) << std::setfill ( '0' ) << systime.wMonth << "-"
			   << std::setw ( 2 ) << std::setfill ( '0' ) << systime.wDay << "-"
			   << std::setw ( 2 ) << std::setfill ( '0' ) << systime.wHour << ":"
			   << std::setw ( 2 ) << std::setfill ( '0' ) << systime.wMinute << ":"
			   << std::setw ( 2 ) << std::setfill ( '0' ) << systime.wSecond;
			return ss.str();
		}
#else // unix like system
		static std::string get_sysctl        ( const std::string&  key ) {
			char result[256];
			size_t size = 256;
			sysctlbyname ( key.c_str(), &result[0], &size, NULL, 0 );
			return std::string ( result );
		}
		static double      get_sysctl_double ( const std::string&  key ) {
			uint64_t result;
			size_t size = sizeof ( result );
			sysctlbyname ( key.c_str(), &result, &size, NULL, 0 );
			return static_cast<double> ( result );
		}
		
		static int         get_sysctl_int    ( const std::string&  key ) {
			int result;
			size_t size = sizeof ( result );
			sysctlbyname ( key.c_str(), &result, &size, NULL, 0 );
			return result;
		}
#endif
	}
	
	
	
        std::string
        SystemInfo::getCpuName ( void )
        {
#ifdef OS_WINDOWS
		return mi::sys::get_cpu_name();
#else
                return mi::sys::get_sysctl ( "machdep.cpu.brand_string" );
#endif
        }

        double
        SystemInfo::getMemorySize ( void )
        {
#ifdef OS_WINDOWS
		return mi::sys::get_memory_size();
#else
                return mi::sys::get_sysctl_double ( "hw.memsize" ) * 1.0 / 1024.0 / 1024.0 / 1024.0;
#endif
        }


        int
        SystemInfo::getNumCores ( void )
        {
#ifdef OS_WINDOWS
		return mi::sys::get_num_cores();
#else
                return mi::sys::get_sysctl_int ( "machdep.cpu.core_count" );
#endif
        }

        std::string
        SystemInfo::getDate ( void )
        {
#ifdef OS_WINDOWS
		return mi::sys::get_date();
#else
                time_t rawtime = std::time ( NULL );
                struct tm* timeinfo = localtime ( &rawtime );
                char buffer [80];
                strftime ( buffer, 80, "%F-%X", timeinfo );
                std::string result ( buffer );
                return result;
#endif
        }
        void
        SystemInfo::print ( std::ostream&  out )
        {
                out << "date: " << mi::SystemInfo::getDate() << std::endl;
                out << "cpu: " << mi::SystemInfo::getCpuName() << "(" << mi::SystemInfo::getNumCores() << "cores)" << std::endl;
                out << "memory:" << mi::SystemInfo::getMemorySize() << "[gb]" << std::endl;
        }

        double
        SystemInfo::getPeakMemorySize ( const SIZE_TYPE type )
        {
                double peakMemory = 0;
#if defined(OS_WINDOWS)
		PROCESS_MEMORY_COUNTERS pmc = { 0 };
		HANDLE hProcess = OpenProcess ( PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId() );
		
		if ( GetProcessMemoryInfo ( hProcess, &pmc, sizeof ( pmc ) ) ) {
			peakMemory = static_cast<double> ( pmc.PeakWorkingSetSize );
		}
			
		CloseHandle ( hProcess );
#else // MAC or Linux
                struct rusage rusage;
                getrusage ( RUSAGE_SELF, &rusage );                ///@todo The result somewhat strange on Mac.
                peakMemory = static_cast<double> ( rusage.ru_maxrss );
#endif // WIN32

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

