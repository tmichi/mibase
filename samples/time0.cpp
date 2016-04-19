#include <mi/Timer.hpp>
#include <vector>
#include <iostream>
#include <unistd.h>
int main ()
{
        mi::Timer timer;
        timer.start ( "test" );
	usleep(1000000);
        timer.end ( "test" );
        std::cerr << timer.toString ( "test" ) <<  std::endl;
        return EXIT_SUCCESS;
}
