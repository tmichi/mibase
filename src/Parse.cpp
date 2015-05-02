#include <mi/Parse.hpp>
#include <string>
#include <cstdlib>
namespace mi {
        template<> char parse ( const std::string& value ) {
                return static_cast<char> ( std::atoi ( value.c_str() ) );
        }

        template<> unsigned char parse ( const std::string& value ) {
                return static_cast<unsigned char> ( std::atoi ( value.c_str() ) );
        }

        template<> short parse ( const std::string& value ) {
                return static_cast<short> ( std::atoi ( value.c_str() ) );
        }

        template<> unsigned short parse ( const std::string& value ) {
                return static_cast<unsigned short> ( std::atoi ( value.c_str() ) );
        }

        template<> int parse ( const std::string& value ) {
                return std::atoi ( value.c_str() );
        }

        template<> unsigned int parse ( const std::string& value ) {
                return static_cast<unsigned int> ( std::atoi ( value.c_str() ) );
        }

        template<> float parse ( const std::string& value ) {
                return static_cast<float> ( std::atof ( value.c_str() ) );
        }

        template<> double parse ( const std::string& value ) {
                return std::atof ( value.c_str() );
        }

        template<> std::string parse ( const std::string& value ) {
                return value;
        }
}//namespace mi

