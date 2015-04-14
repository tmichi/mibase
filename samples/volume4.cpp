#include <mi/VolumeData.hpp>
int main ( int argc, char** argv )
{
        mi::Point3i size( 10, 10, 10 );
        mi::Point3d pitch( 0.5, 0.5, 0.5 );
        mi::Point3d origin( 0, 0, 0 );
        mi::VolumeInfo info0( size, pitch, origin );
        mi::VolumeData<short> vol0 ( info0 );

        mi::VolumeInfo info1;
        mi::VolumeData<short> vol1;
        info1.setSize( size ).setPitch( pitch ).setOrigin( origin );
        vol1.allocate();
        vol1.deallocate();

        mi::Point3i p( -1, 3, 4 );
        if( !info1.isValid( p ) ) {
                std::cerr<<"( -1, 3, 4) is out-of range"<<std::endl;
        }
        mi::Point3i p1( 1, 3, 4 );
        mi::Point3d x = info1.getPointInSpace ( p1 );

        int index = info1.toIndex( p1 );
        std::cerr<<"index : "<<index<<std::endl;

        return 0;
}
