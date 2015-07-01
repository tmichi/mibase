#include <mi/FileLister.hpp>
#include <iostream>
int main ( int argc, char** argv )
{

        std::vector<std::string> result;
//	mi::FileLister::list("../samples/", "txt,cpp", result);
        mi::FileLister::list ( "../sample/", "txt,cpp", result );
        std::cerr << result.size() << " file found" << std::endl;

        for ( size_t i = 0 ; i < result.size(); ++i ) {
                std::cerr << i << ":" << result[i] << std::endl;
        }

        return 0;
}
