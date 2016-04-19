#ifndef MI_SYSTEM_INFO_INTERNAL_WINDOWS_HPP
#define MI_SYSTEM_INFO_INTERNAL_WINDOWS_HPP 1
#ifdef OS_WINDOWS
#include <windows.h>
#include <process.h>
#include <intrin.h>
#include <Psapi.h>
#pragma comment(lib, "psapi.lib")

namespace mi
{
	namespace internal {
		class SystemInfoInternal {
		public:
			SystemInfoInternal ( void ) {
				;
			}
			~SystemInfoInternal ( void ) {
				;
			}
			virtual std::string getCpuName ( void ) const {
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
			virtual
			double getMemorySize( void ) const {
				MEMORYSTATUSEX stat;
				stat.dwLength = sizeof ( MEMORYSTATUSEX );
				
				if ( GlobalMemoryStatusEx ( &stat ) == 0 ) {
					std::cerr << "error while calling GlobalMemoryStatusEx()" << std::endl;
					return 0;
				}
				const double memorySize = static_cast<double> ( stat.ullTotalPhys / 1024.0 / 1024 / 1024 ) ;
				return memorySize;
			}
			virtual 
			int getNumCores( void ) const {
				SYSTEM_INFO sysinfo;
				GetSystemInfo ( &sysinfo );
				return static_cast<int> ( sysinfo.dwNumberOfProcessors );
			}
			virtual 
			std::string getDate( void ) const {
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
			virtual double getPeakMemory( void ) const {
				double peakMemory = 0;
				PROCESS_MEMORY_COUNTERS pmc = { 0 };
				HANDLE hProcess = OpenProcess ( PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId() );
				if ( GetProcessMemoryInfo ( hProcess, &pmc, sizeof ( pmc ) ) ) {
					peakMemory = static_cast<double> ( pmc.PeakWorkingSetSize );
				}
				CloseHandle ( hProcess );
				return peakMemory;
			}
			static SystemInfoInternal& getInstance(void) {
				static SystemInfoInternal instance;
				return instance;
			}
			
		};
	}
}
#endif //OS_WINDOWS
#endif //MI_SYSTEM_INFO_INTERNAL_WINDOWS_HPP

