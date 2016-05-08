#ifndef MI_NON_COPYABLE_HPP
#define MI_NON_COPYABLE_HPP 1
namespace mi
{
        class NonCopyable
        {
        private:
                NonCopyable ( const NonCopyable& that );
                void operator = ( const NonCopyable& that );
        public:
                NonCopyable ( void )
                {
                        return;
                }
                virtual ~NonCopyable ( void )
                {
                        ;
                }
        };
}
#endif //MI_NON_COPYABLE_HPP
