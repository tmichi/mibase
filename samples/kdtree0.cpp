#include <mi/Kdtree.hpp>
#include <mi/math.hpp>
#include <vector>
#include <iostream>
int main ( int argc, char** argv )
{

        std::vector<mi::Vector3d> p;
        for( int i = 0 ; i < 10000 ; i++ ) {
                double x = ( rand() % 2001 - 1000 ) * 0.001;
                double y = ( rand() % 2001 - 1000 ) * 0.001;
                double z = ( rand() % 2001 - 1000 ) * 0.001;
                p.push_back( mi::Vector3d( x,y,z ) );
        }

        mi::Kdtree<mi::Vector3d> kdtree( p ) ;

        mi::Vector3d v( 0.1, 0.1, 0.1 ) ;
        std::list<mi::Vector3d> result;

        kdtree.find( v, 0.1, result, true );
        for( std::list<mi::Vector3d>::iterator iter = result.begin(); iter != result.end() ; ++iter ) {
                mi::Vector3d& v0 = *iter;
                mi::Vector3d d = *iter - v;
                double sqrtDist = d.x()*d.x()+d.y()*d.y()+d.z()*d.z();
                std::cerr<<v0.x()<<" "<<v0.y()<<" "<<v0.z()<<" "<<sqrtDist<<std::endl;
        }
        return 0;
}
