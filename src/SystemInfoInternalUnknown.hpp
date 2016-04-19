#ifndef MI_SYSTEM_INFO_INTERNAL_UNKNOWN_HPP
#define MI_SYSTEM_INFO_INTERNAL_UNKNOWN_HPP 1

namespace mi
{
	namespace internal {
		class SystemInfoInternalUnknown : public SystemInfoInternal {
		public:
			SystemInfoInternalUnknown ( void ) {
				;
			}
			~SystemInfoInternalUnknown ( void ) {
				;
			}
			virtual std::string getCpuName ( void ) const {
				return std::string();
			}
			virtual double getMemorySize( void ) const {
				return 0;
			}
			virtual int getNumCores( void ) const {
				return 1;
			}
			virtual std::string getDate( void ) const {
				return std::string();
			}
			virtual double getPeakMemory( void ) const {
				return 0;
			}
		};
	}
}

#endif //MI_SYSTEM_INFO_INTERNAL_UNKNOWN_HPP
