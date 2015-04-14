#include <mi/VolumeData.hpp>
#include <mi/VolumeDataCreator.hpp>
#include <mi/VolumeDataUtility.hpp>
#include <mi/Mesh.hpp>
#include <mi/MeshUtility.hpp>
int main ( int argc, char** argv )
{
        mi::VolumeData<short> vol0 ( 10, 10, 10 );
        mi::VolumeDataCreator<short> creator( vol0, 0 );
        creator.setValue( 8 ).fillSphere( mi::Point3i( 5,5,5 ), 3 );

        mi::Mesh mesh;
        mi::VolumeDataUtility::polygonize( vol0, mesh, 0.5 );
        std::cerr<<"#v:"<<mesh.getNumVertices()<<std::endl;
        std::cerr<<"#f:"<<mesh.getNumFaces()<<std::endl;
        mi::MeshUtility::save( mesh, "mesh.stl" );
        mi::MeshUtility::save( mesh, "mesh.off" );
        mi::MeshUtility::save( mesh, "mesh.ply" );
        mi::MeshUtility::save( mesh, "mesh.obj" );
        return 0;
}
