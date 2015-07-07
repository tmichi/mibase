#include <mi/TestCase.hpp>
class TestCaseTest : public mi::TestCase
{
private:
        void init ( void )
        {
                this->add ( TestCaseTest::test_int    );
                this->add ( TestCaseTest::test_double );
                return;
        }

        static void test_int ( void )
        {
                const int a = 4;
                ASSERT_EQUALS ( 4, a ) ;
                return;
        }

        static void test_double ( void )
        {
                const double b = 0.5;
                ASSERT_EPSILON_EQUALS ( 0.50001, b, 1.0e-3 );
                return;
        }
};
INIT_TEST ( TestCaseTest );

