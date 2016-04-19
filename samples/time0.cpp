#include <mi/Timer.hpp>
#include <vector>
#include <iostream>
int main ()
{
        mi::Timer timer;
        timer.start ( "test" );
        for (int i = 0; i < 100; ++i) {
                for (int j = 0; j < 100; ++j) {
                        std::cerr << "*";
                }
        }
        timer.end ( "test" );
        std::cerr << timer.toString ( "test" ) <<  std::endl;
        return EXIT_SUCCESS;
}
