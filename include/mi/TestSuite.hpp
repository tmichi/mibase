/**
 * @file TestSuite.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_TEST_SUITE_HPP
#define MI_TEST_SUITE_HPP 1
#include <string>
namespace mi
{
        class TestCase;
        /**
         * @class TestSuite "TestSuite.hpp"  "mi/TestSuite.hpp"
         * @brief Test suite class.
         * @sa TestCase
         */
        class TestSuite
        {
        private:
                TestSuite ( const TestSuite& that );
                void operator = ( const TestSuite& that );
                TestSuite ( void );
                ~TestSuite ( void );
        public:
                /**
                 * @brief Get instance.
                 * @return Instance.
                 */
                static TestSuite& getInstance ( void );

                /**
                 * @brief Add test case.
                 */
                void add ( TestCase* testcase );

                /**
                 * @brief Run test cases.
                 */
                int run ( const std::string& testname );
        private:
                static std::string replace_str ( const std::string& inStr );
        private:
                class Impl;
                Impl* _impl;
        };
}
#endif //MI_TEST_SUITE_HPP
