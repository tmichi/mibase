/**
 * @file octree.cpp
 * @brief Octree example code.
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <iostream>
#include <mi/Octree.hpp>
#include <mi/OctreeImporter.hpp>
#include <mi/OctreeExporter.hpp>

int main ( void )
{
        mi::Octree<short> oct( 32, 0 ); //Create 32 x 32 x 32 octree ( 5 levels ).
        oct.set( 20, 30, 0, 4 );
        if ( !mi::OctreeExporter<short>( oct ).write( "out.oct" ) ) return -1;

        mi::Octree<short> oct2;
        if ( !mi::OctreeImporter<short>( oct2 ).read( "out.oct" ) ) return -2;

        std::cerr<<( int )oct.get( 20,30,0 )<<" "<<( int )oct2.get( 20,30,0 )<<std::endl;
        return 0;
}
