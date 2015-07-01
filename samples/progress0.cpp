#include <mi/Progress.hpp>

int main ( int argc, char** argv )
{
        int n = 100000;
        mi::Progress progress ( n, mi::Progress::getWidth ( n ) ) ;
        int i = 0;

        while ( !progress.end() ) {
                progress.addCounter();
                ++i;
                progress.print();
        }

        std::cerr << std::endl;
        std::cerr << i << " ok\n";
        return 0;
}
