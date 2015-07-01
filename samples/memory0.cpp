/**
 * @file memory0.cpp
 * @brief Test code for checking memory usage.
 * @author Takashi Michikawa <michi@den.rcast.u-tokyo.ac.jp>
 */
#include <mi/SystemInfo.hpp>
#include <vector>
#include <iostream>
int main ( int argc, char** argv )
{
        double before =  mi::SystemInfo::getPeakMemorySize();
        std::cerr << "before : " << before << "[mb]\n";
        std::vector<char> array ( 1024 * 1024, 0 ); // 1MB
        double after = mi::SystemInfo::getPeakMemorySize();
        std::cerr << "after :" << after << "[mb]\n";
        std::cerr << "diff :" << after - before << "[mb]\n";
        return EXIT_SUCCESS;
}
