#include <mi/TestSuite.hpp>
class SampleTest : public mi::TestCase
{
public:
        SampleTest ( void )
        {
                mi::TestSuite::getInstance().add( this );
                return;
        }
private:
        void init( void )
        {
                this->add( SampleTest::test0 );
                this->add( SampleTest::test1 );
                return;
        }

        static void test0( void )
        {
                ASSERT_EQUALS( 4, 4 );
                return;
        }

        static void test1( void )
        {
                ASSERT_EPSILON_EQUALS( 10.0, 10.00001, 1.0e-3 );
                return;
        }
};
static SampleTest test;

int main( int argc, char** argv )
{
        return mi::TestSuite::getInstance().run();
}
