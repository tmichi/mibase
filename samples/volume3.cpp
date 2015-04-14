#include <mi/VolumeData.hpp>
#include <mi/VolumeDataCreator.hpp>
#include <mi/Range.hpp>
int main ( int argc, char** argv )
{
        mi::VolumeData<short> vol0 ( 10, 10, 10 );
        const mi::Point3i& size = vol0.getSize();

        mi::VolumeDataCreator<short> creator( vol0, 0 );
        creator.setValue( 8 ).fillSphere( mi::Point3i( 5,5,5 ), 3 );
        mi::Point3i bmin( 5, 5, 5 );
        mi::Point3i bmax( 8, 8, 8 );
        mi::Range range( bmin, bmax );

        for ( mi::Range::iterator iter = range.begin() ; iter != range.end() ; ++iter ) {
                mi::Point3i& p = *iter;
                vol0.set ( p, 3 );
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
