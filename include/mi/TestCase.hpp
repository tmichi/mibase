/**
* @file TestCase.hpp
* @author Takashi Michikawa <michikawa@acm.org>
*/

#pragma once
#ifndef MI_TEST_CASE_HPP
#define MI_TEST_CASE_HPP 1
#include <list>
#include <iostream>

namespace mi
{
        /**
         * @class TestCase "TestCase.hpp"  <mi/TestCase.hpp>
         * @brief Basic class for writing test cases.
         * @sa TestSuite
         */
        class TestCase
        {
        private:
                TestCase ( const TestCase& that );
                void operator = ( const TestCase& that );
        protected:
                /**
                 * @brief Constructor
                 */
                TestCase ( void );
        public:
                /**
                 * @brief Destructor
                 */
                virtual ~TestCase ( void );
                /**
                 * @brief Add a test to the test suite
                 * @param [in] test Test case
                 */
                void add ( void ( * test ) ( void ) );
                /**
                 * @brief Start tests
                 */
                void run ( void );
                /**
                 * @brief Get the number of errors.
                 * @return The number of errors.
                 */
                static int getNumErrors ( void );
                /**
                 * @brief Print errors
                 */
                static void print ( std::ostream& fout );
        protected:
                /**
                 * @brief initialization
                 */
                virtual void init ( void ) = 0;
                /**
                 * @brief clean up
                 */
                virtual void term ( void );

                /**
                 * @brief Check two value are same.
                 * @param [in] expectedValue Expected value.
                 * @param [in] actualValue Actual value.
                 */
#define ASSERT_EQUALS(expectedValue, actualValue)			\
		if(!TestCase::checkEquals( __FILE__, __LINE__, expectedValue, actualValue))return
                /**
                 * @brief Check two value are almost same within a threshold.
                 * @param [in] expectedValue Expected value.
                 * @param [in] actualValue Actual value.
                 * @param [in] epsilon Threshold.
                 */
#define ASSERT_EPSILON_EQUALS(expectedValue, actualValue, epsilon)	\
		if(!TestCase::checkEpsilonEquals( __FILE__, __LINE__, expectedValue, actualValue, epsilon))return

                /**
                 * @brief Check the values are exactly same.
                 * @param [in] filename The filename of the test
                 * @param [in] lineNo Line number of the test
                 * @param [in] expectedValue The expected value
                 * @param [in] actualValue The acutual value
                 * @retval true Same.
                 * @retval false Different.
                 */
                template< typename T>
                static bool checkEquals ( const char* fileName, const int lineNo,  const T expectedValue, const T actualValue );
                /**
                 * @brief Check the values are exactly same.
                 * @param [in] filename The filename of the test
                 * @param [in] lineNo Line number of the test
                 * @param [in] expectedValue The expected value
                 * @param [in] actualValue The acutual value
                 * @param [in] epsilon Accepted torelance
                 * @retval true Same.
                 * @retval false Different.
                 */
                template <typename T>
                static bool checkEpsilonEquals ( const char* fileName, const int lineNo,  const T expectedValue, const T actualValue, const T epsilon = T() );
        private:
                template< typename T>
                static void add_message ( const char* fileName, const int lineNo, const T expectedValue, const T actualValue, const T epsilon = T(), const bool isExact = true );
                static std::list<std::string>& get_message ( void );
        private:
                class Impl;
                Impl* _impl;
        };
#define INIT_TEST(TYPE) static TYPE test
}
#endif//  MI_TEST_CASE_HPP
