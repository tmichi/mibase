/**
* @file TestCase.cpp
* @author Takashi Michikawa <michikawa@acm.org>
*/
#include <mi/TestCase.hpp>
#include <mi/TestSuite.hpp>
#include <sstream>
#include <list>
#include <cmath>
#include <iostream>

namespace mi
{
        class TestCase::Impl
        {
        public:
                Impl ( void )
                {
                        return;
                }
                ~Impl ( void )
                {
                        return;
                }

                void add ( void ( * test ) ( void ) )
                {
                        this->_tests.push_back ( test );
                }

                std::list<void ( * ) ( void )>::iterator begin ( void )
                {
                        return this->_tests.begin();
                }

                std::list<void ( * ) ( void )>::iterator end ( void )
                {
                        return this->_tests.end();
                }
        private:
                std::list<void ( * ) ( void )> _tests;
        };

        TestCase::TestCase ( void ) : _impl ( new TestCase::Impl () )
        {
                mi::TestSuite::getInstance().add ( this );
                return ;
        }

        TestCase::~TestCase ( void )
        {
                return;
        }

        void
        TestCase::add ( void ( * test ) ( void ) )
        {
                this->_impl->add ( test );
                return;
        }

        void
        TestCase::run ( void )
        {
                this->init();

                for ( std::list<void ( * ) ( void )>::iterator iter = this->_impl->begin() ; iter != this->_impl->end() ; ++iter ) {
                        const int numError = TestCase::getNumErrors();
                        ( *iter )();

                        if ( numError == TestCase::getNumErrors() ) {
                                std::cerr << ".";
                        } else {
                                std::cerr << "F";
                        }
                }

                this->term();
                return;
        }

        int
        TestCase::getNumErrors ( void )
        {
                return static_cast<int> ( TestCase::get_message().size() );
        }

        void
        TestCase::print ( std::ostream& out )
        {
                std::list<std::string>& message = TestCase::get_message();

                for ( std::list<std::string>::iterator iter = message.begin() ; iter != message.end() ; ++iter ) {
                        out << ( *iter ) << std::endl;
                }

                return;
        }

        void
        TestCase::term ( void )
        {
                return;
        }

        template< typename T>
        bool
        TestCase::checkEquals ( const char* fileName, const int lineNo,  const T expectedValue, const T actualValue )
        {
                if ( expectedValue != actualValue ) {
                        TestCase::add_message ( fileName, lineNo, expectedValue, actualValue );
                        return false;
                }

                return true;
        }
        template <typename T>
        bool
        TestCase::checkEpsilonEquals ( const char* fileName, const int lineNo,  const T expectedValue, const T actualValue, const T epsilon )
        {
                if ( std::fabs ( expectedValue - actualValue ) > epsilon ) {
                        TestCase::add_message ( fileName, lineNo, expectedValue, actualValue, epsilon, false );
                        return false;
                }

                return true;
        }

        template< typename T>
        void
        TestCase::add_message ( const char* fileName, const int lineNo, const T expectedValue, const T actualValue, const T epsilon, const bool isExact )
        {
                std::stringstream ss;
                ss << fileName << ":" << lineNo << ": error. expected value = <" << expectedValue << ">" << ", actual value = <" << actualValue << ">";

                if ( !isExact ) {
                        ss << ", epsilon=<" << epsilon << ">";
                }

                TestCase::get_message().push_back ( ss.str() );
                return;
        }

        std::list<std::string>&
        TestCase::get_message ( void )
        {
                static std::list< std::string > message;
                return message;
        }

#define TEST_CASE__CHECK_EQUALS(T) template bool TestCase::checkEquals<T> ( const char* fileName, const int lineNo,  const T expectedValue, const T actualValue )
        TEST_CASE__CHECK_EQUALS ( unsigned char );
        TEST_CASE__CHECK_EQUALS ( char );
        TEST_CASE__CHECK_EQUALS ( unsigned short );
        TEST_CASE__CHECK_EQUALS ( short );
        TEST_CASE__CHECK_EQUALS ( unsigned int );
        TEST_CASE__CHECK_EQUALS ( int );
        TEST_CASE__CHECK_EQUALS ( float );
        TEST_CASE__CHECK_EQUALS ( double );
        TEST_CASE__CHECK_EQUALS ( std::string );

#define TEST_CASE__CHECK_EPSILON_EQUALS(T) template bool TestCase::checkEpsilonEquals<T> ( const char* fileName, const int lineNo,  const T expectedValue, const T actualValue, const T epsilon )
        TEST_CASE__CHECK_EPSILON_EQUALS ( unsigned char );
        TEST_CASE__CHECK_EPSILON_EQUALS ( char );
        TEST_CASE__CHECK_EPSILON_EQUALS ( unsigned short );
        TEST_CASE__CHECK_EPSILON_EQUALS ( short );
        TEST_CASE__CHECK_EPSILON_EQUALS ( unsigned int );
        TEST_CASE__CHECK_EPSILON_EQUALS ( int );
        TEST_CASE__CHECK_EPSILON_EQUALS ( float );
        TEST_CASE__CHECK_EPSILON_EQUALS ( double );

#define TEST_CASE__ADD_MESSAGE(T) template void TestCase::add_message<T> ( const char* fileName, const int lineNo, const T expectedValue, const T actualValue, const T epsilon, const bool isExact)
        TEST_CASE__ADD_MESSAGE ( unsigned char );
        TEST_CASE__ADD_MESSAGE ( char );
        TEST_CASE__ADD_MESSAGE ( unsigned short );
        TEST_CASE__ADD_MESSAGE ( short );
        TEST_CASE__ADD_MESSAGE ( unsigned int );
        TEST_CASE__ADD_MESSAGE ( int );
        TEST_CASE__ADD_MESSAGE ( float );
        TEST_CASE__ADD_MESSAGE ( double );
        TEST_CASE__ADD_MESSAGE ( std::string );

}

