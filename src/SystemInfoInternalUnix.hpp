#ifndef MI_SYSTEM_INFO_INTERNAL_UNIX_HPP
#define MI_SYSTEM_INFO_INTERNAL_UNIX_HPP 1
#ifdef OS_UNIX
#include <ctime>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/resource.h>

namespace mi
{
        namespace internal
        {
                class SystemInfoInternal
                {
                public:
                        SystemInfoInternal ( void )
                        {
                                ;
                        }

                        ~SystemInfoInternal ( void )
                        {
                                ;
                        }

                        virtual std::string getCpuName ( void ) const
                        {
                                return mi::internal::SystemInfoInternal::get_sysctl ( "machdep.cpu.brand_string" );
                        }

                        virtual double getMemorySize( void ) const
                        {
                                return mi::internal::SystemInfoInternal::get_sysctl_double ( "hw.memsize" ) * 1.0 / 1024.0 / 1024.0 / 1024.0;
                        }
                        virtual int getNumCores( void ) const
                        {
                                return mi::internal::SystemInfoInternal::get_sysctl_int ( "machdep.cpu.core_count" );
                        }
                        virtual std::string getDate( void ) const
                        {
                                time_t rawtime = std::time ( NULL );
                                struct tm* timeinfo = localtime ( &rawtime );
                                char buffer [80];
                                strftime ( buffer, 80, "%F-%X", timeinfo );
//				std::string result ( buffer );
//				return result;
                                return std::string( buffer );
                        }
                        virtual double getPeakMemory( void ) const
                        {
                                double peakMemory = 0;
                                struct rusage rusage;
                                getrusage ( RUSAGE_SELF, &rusage );                ///@todo The result somewhat strange on Mac.
                                peakMemory = static_cast<double> ( rusage.ru_maxrss );
                                return peakMemory;
                        }

                        static SystemInfoInternal& getInstance( void )
                        {
                                static SystemInfoInternal instance;
                                return instance;
                        }

                private:
                        static std::string get_sysctl        ( const std::string&  key )
                        {
                                char result[256];
                                size_t size = 256;
                                sysctlbyname ( key.c_str(), &result[0], &size, NULL, 0 );
                                return std::string ( result );
                        }
                        static double      get_sysctl_double ( const std::string&  key )
                        {
                                uint64_t result;
                                size_t size = sizeof ( result );
                                sysctlbyname ( key.c_str(), &result, &size, NULL, 0 );
                                return static_cast<double> ( result );
                        }
                        static int get_sysctl_int    ( const std::string&  key )
                        {
                                int result;
                                size_t size = sizeof ( result );
                                sysctlbyname ( key.c_str(), &result, &size, NULL, 0 );
                                return result;
                        }
                };
        }
}
#endif //OS_UNIX
#endif //MI_SYSTEM_INFO_INTERNAL_UNIX_HPP
