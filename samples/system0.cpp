#include <mi/SystemInfo.hpp>
#include <iostream>

int main ( int argc, char** argv )
{
	std::cerr<<"cpu name: "<<mi::SystemInfo::getCpuName()<<std::endl;
	std::cerr<<"mem size: "<<mi::SystemInfo::getMemorySize()<<"[gb]"<<std::endl;
	std::cerr<<"date: "<<mi::SystemInfo::getDate()<<std::endl;
        std::cerr<<"#cores: "<<mi::SystemInfo::getNumCores()<<std::endl;
        return 0;
}
