#ifndef MI_SYSTEM_INFO_INTERNAL_CYGWIN_HPP
#define MI_SYSTEM_INFO_INTERNAL_CYGWIN_HPP 1
#ifdef OS_CYGWIN
#include "SystemInfoInternal.hpp"
#include <ctime>

namespace mi
{
        namespace internal
        {
                /// @todo Not implemented yet.
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
                                return std::string( "Good CPU" );
                        }
                        virtual double getMemorySize( void ) const
                        {
                                return 0;
                        }
                        virtual int getNumCores( void ) const
                        {
                                return 1;
                        }
                        virtual std::string getDate( void ) const
                        {
                                time_t rawtime = std::time ( NULL );
                                struct tm* timeinfo = localtime ( &rawtime );
                                char buffer [80];
                                strftime ( buffer, 80, "%F-%X", timeinfo );
                                std::string result ( buffer );
                                return result;
                        }
                        virtual double getPeakMemory( void ) const
                        {
                                double peakMemory = 0;

                                return peakMemory;

                        }

                        static SystemInfoInternal& getInstance( void )
                        {
                                static SystemInfoInternal instance;
                                return instance;
                        }


                };
        }
}
#endif //OS_CYGWIN
#endif //MI_SYSTEM_INFO_INTERNAL_CYGWIN_HPP
