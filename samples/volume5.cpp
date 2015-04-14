#include <iostream>
#include <mi/Range.hpp>
#include <mi/VolumeData.hpp>
#include <mi/VolumeDataUtility.hpp>

int main ( int argc, char** argv )
{
        mi::VolumeData<char> data( 50, 50, 50 );
        mi::Range range ( data.getInfo().getMin(),  data.getInfo().getMax() );
        for( mi::Range::iterator iter = range.begin() ; iter != range.end() ; ++iter ) {
                data.set( *iter, 10 );
        }

        if ( !mi::VolumeDataUtility::save( data,  "sample.raw" ) ) return -1;
        data.deallocate(); // release memory.

        mi::VolumeData<char> data2( data.getInfo() );
        if ( !mi::VolumeDataUtility::open( data2, "sample.raw" ) ) return -2;
        std::cerr<<"ok"<<std::endl;
        return 0;
}
