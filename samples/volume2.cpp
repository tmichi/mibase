#include <mi/VolumeData.hpp>
#include <mi/VolumeDataCreator.hpp>
int main ( int argc, char** argv )
{
        mi::VolumeData<short> vol0 ( 10, 10, 10 );
        const mi::Point3i& size = vol0.getSize();

        mi::VolumeDataCreator<short> creator( vol0, 0 );
        creator.setValue( 8 ).fillSphere( mi::Point3i( 5,5,5 ), 3 );

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
