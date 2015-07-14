#include <mi/TestCase.hpp>
#include "type2str.hpp"
class Type2StrTest : public mi::TestCase
{
private:
        void init ( void )
        {
                this->add ( Type2StrTest::test_all    );
                return;
        }

        static void test_all ( void )
      {
                ASSERT_EQUALS ( std::string("char"), mi::type2str<char>()) ;
                ASSERT_EQUALS ( std::string("uchar"), mi::type2str<unsigned char>()) ;
                ASSERT_EQUALS ( std::string("short"), mi::type2str<short>()) ;
                ASSERT_EQUALS ( std::string("ushort"), mi::type2str<unsigned short>()) ;
                ASSERT_EQUALS ( std::string("int"), mi::type2str<int>()) ;
                ASSERT_EQUALS ( std::string("uint"), mi::type2str<unsigned int>()) ;
                ASSERT_EQUALS ( std::string("float"), mi::type2str<float>()) ;
                ASSERT_EQUALS ( std::string("double"), mi::type2str<double>()) ;
              return;
        }
};
INIT_TEST ( Type2StrTest );

