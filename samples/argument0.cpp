#include <mi/Argument.hpp>
#include <iostream>
#include <string>
int main( int argc, char** argv )
{
        mi::Argument arg( argc, argv );
        std::string stri = arg.get<std::string>( "-i" );
        double v1        = arg.get<double>( "-v1" );
        int v2           = arg.get<int>( "-v2" );;

        std::cerr<<" -i : "<<stri<<std::endl;
        std::cerr<<" -v1 : "<<v1<<std::endl;
        std::cerr<<" -v2 : "<<v2<<std::endl;

        return EXIT_SUCCESS;
}
