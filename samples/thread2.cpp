#include <mi/ParallelFor.hpp>
#include <functional>
#include <vector>
#include <cstdlib>
class binarize : public std::unary_function<int, void>
{
private:
        int  _threshold;
public:
        binarize ( const int threshold ) : _threshold ( threshold )
        {
                return;
        }
        void operator () ( int & v ) const
        {
                v = ( v < this->_threshold ) ? 0 : 1;
        }
};

int main( int argc, char** argv )
{
        std::vector<int> array;
        for( int i = 0 ; i < 1000000 ; i++ )  array.push_back( rand() );
        mi::parallel_for_each( array.begin(), array.end(), binarize( 10 ), 10000 );
        return 0;
}
