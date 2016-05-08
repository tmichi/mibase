#include <mi/Tokenizer.hpp>
#include <vector>
#include <cstdlib>

int main ( int argc, char** argv )
{
	std::string str0 ( "ls -1 -d 400 -x 200 ");
	mi::Tokenizer tokenizer ( str0 );
	
	if ( tokenizer.size() != 6 ) {
		return -1;
	}

	std::cerr<<" input : "<< str0<<std::endl;
	for ( int i = 0 ; i < tokenizer.size() ; ++i ) {
		std::cerr<<i << " : "<< tokenizer.get(i)<<std::endl;
	}
	
        return 0;
}
