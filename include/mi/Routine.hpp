#ifndef MI_ROUTINE_HPP
#define MI_ROUTINE_HPP 1
#include <string>
#include <memory>
#include "NonCopyable.hpp"
namespace mi
{
        /**
         * @class Routine Routine.
         */
        class Routine : public NonCopyable
        {
        private:
                class Impl;
                std::unique_ptr<Impl> _impl;
        protected:
                /**
                 * @brief Constructor
                 * @param [in] name Routine name
                 */
                explicit Routine ( const std::string& name );
        public:
                /**
                 * @brief Destructor
                 */
                virtual ~Routine ( void );
                /**
                 * @brief Get Instance.
                 */
                Routine* getInstance ( void );
                static bool run ( Routine* routine );
                static void setDebugModeOn ( void );
		
		Routine& setTempFileNameHeader ( const std::string& fileName ) ;
        protected:
                std::stringstream& stream ();
		std::string create_temp_file_name ( const std::string& footer ) const;

                virtual bool run_main_routine ( void );
		
                bool check ( void ) const ;
                void set_failed ( void ) ;
                /**
                 * @brief Check debug mode.
                 * @retval true Debug mode.
                 * @retval false Release mode.
                 */
                static bool is_debug_mode ( void );
        };
}

#endif // MI_ROUTINE_HPP
