/**
 * @file TestSuite.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_TEST_SUITE_HPP
#define MI_TEST_SUITE_HPP 1
#include <string>
#include <memory>
#include "NonCopyable.hpp"
namespace mi
{
        class TestCase;
        /**
         * @class TestSuite "TestSuite.hpp"  "mi/TestSuite.hpp"
         * @brief Test suite class.
         * @sa TestCase
         */
        class TestSuite : public NonCopyable
        {
        private:
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
		std::unique_ptr<Impl> _impl;
        };
}
#endif //MI_TEST_SUITE_HPP
