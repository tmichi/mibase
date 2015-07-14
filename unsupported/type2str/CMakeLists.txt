ADD_EXECUTABLE(type2strTest Type2StrTest.cpp type2str.hpp  main.cpp)
TARGET_LINK_LIBRARIES(type2strTest mibase)
ADD_TEST(type2str type2strTest) #for CTest


