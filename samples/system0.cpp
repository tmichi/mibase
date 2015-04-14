#include <mi/System.hpp>
#include <iostream>

int main ( int argc, char** argv )
{
        std::cerr<<"#cores:"<<mi::System::getNumCores()<<std::endl;


        return 0;
}
