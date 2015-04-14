#include <mi/VolumeData.hpp>

int main ( int argc, char** argv )
{
        mi::VolumeData<short> vol0 ( 10, 10, 10 );
        const mi::Point3i& size = vol0.getSize();

        for ( int z = 0 ; z < size.z() ; ++z ) {
                for ( int y = 0 ; y < size.y() ; ++y ) {
                        for ( int x = 0 ; x < size.x() ; ++x ) {
                                const short value = x + y + z ;
                                vol0.set ( x, y, z , value );
                        }
                }
        }

        for ( int z = 0 ; z < size.z() ; ++z ) {
                for ( int y = 0 ; y < size.y() ; ++y ) {
                        for ( int x = 0 ; x < size.x() ; ++x ) {
                                const mi::Point3i p( x,y,z );
                                const short value = vol0.get( p );
                                std::cerr<<value<<" ";
                        }
                        std::cerr<<std::endl;
                }
                std::cerr<<std::endl;
        }

        return 0;
}
