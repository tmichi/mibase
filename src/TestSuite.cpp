/**
 * @file TestSuite.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/TestSuite.hpp>
#include <mi/TestCase.hpp>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
namespace mi
{
        class TestSuite::Impl
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

                void add ( TestCase* test )
                {
                        this->_testcases.push_back ( test );
                }

                std::list<TestCase*>::iterator begin ( void )
                {
                        return this->_testcases.begin();
                }

                std::list<TestCase*>::iterator end ( void )
                {
                        return this->_testcases.end();
                }
        private:
                std::list< TestCase* > _testcases; ///< A set of test cases.
        };


        TestSuite::TestSuite ( void ) : _impl ( new TestSuite::Impl () )
        {
                return;
        }

        TestSuite::~TestSuite ( void )
        {
                if ( this->_impl != NULL ) {
                        delete this->_impl;
                        this->_impl = NULL;
                }

                return;
        }

        TestSuite&
        TestSuite::getInstance ( void )
        {
                static TestSuite instance;
                return instance;
        }

        void
        TestSuite::add ( TestCase* testcase )
        {
                this->_impl->add ( testcase );
                return;
        }

        int
        TestSuite::run ( const std::string& testname )
        {
                for ( std::list<TestCase*>::iterator iter = this->_impl->begin() ; iter != this->_impl->end() ; ++iter ) {
                        ( *iter )->run();
                }

                std::cerr << std::endl;

                if ( TestCase::getNumErrors() == 0 ) {
                        return  EXIT_SUCCESS;
                }

                std::stringstream ss;
                ss << testname << ".log";
                std::ofstream fout ( ss.str().c_str() );
                TestCase::print ( fout );
                std::cerr << "error(s) found. see " << ss.str() << "." << std::endl;
                return EXIT_FAILURE;
        }

        std::string
        TestSuite::replace_str ( const  std::string& inStr )
        {
                std::string str = inStr;
                const std::string rep_str ( "-" );
                const std::string space_str ( " " );

                for ( std::string::size_type pos = str.find ( space_str ) ; pos != std::string::npos ; pos = str.find ( space_str, rep_str.length() + pos ) ) {
                        str.replace ( pos, space_str.length(), rep_str );
                }

                const std::string colon_str ( ":" );

                for (  std::string::size_type pos = str.find ( colon_str ) ; pos != std::string::npos ; pos = str.find ( colon_str, rep_str.length() + pos ) ) {
                        str.replace ( pos, colon_str.length(), rep_str );
                }

                return str;
        }
}
