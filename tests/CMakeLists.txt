ADD_EXECUTABLE(test0 TestCaseTest.cpp test0.cpp)
TARGET_LINK_LIBRARIES(test0 mibase)

ADD_TEST(mitest test0) #for CTest
	





