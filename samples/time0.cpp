#include <mi/Timer.hpp>
#include <vector>
#include <iostream>
int main ()
{
        mi::Timer timer;
        timer.start ( "test" );
        int count = 0;

        for ( int i = 0 ; i < 10000; ++i ) {
                for ( int j = 0 ; j < 10000; ++j ) {
                        count += 1;
                }
        }

        timer.end ( "test" );
        std::cerr << timer.toString ( "test" ) << std::endl;
        return EXIT_SUCCESS;
}
