#ifndef MI_ROUTINE_HPP
#define MI_ROUTINE_HPP 1
#include <sstream>
namespace mi
{
        /**
         * @class Routine Routine.
         */
        class Routine
        {
        private:
		class Impl;
		Impl* _impl;
        protected:
                Routine ( const std::string& name );
	private: // non copyable
		Routine ( const Routine& that ) ;
		void operator = ( const Routine& that ) ;
	public:
                virtual ~Routine ( void );
		Routine* getInstance ( void );
                static bool run ( Routine* routine );
                static void setDebugModeOn( void );
        protected:
                std::stringstream& stream ();
		
                virtual bool run_main_routine( void );
                bool check ( void ) const ;
		void set_failed( void ) ;
                /**
                 * @brief Check debug mode.
                 * @retval true Debug mode.
                 * @retval false Release mode.
                 */
                static bool is_debug_mode ( void );
        };
}

#endif // MI_ROUTINE_HPP
