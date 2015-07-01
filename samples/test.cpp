#include <iostream>
#include <mi/AttributeSet.hpp>
int main ( int argc, char** argv )
{

        mi::Argument arg ( argc, argv ) ;
        int t;
        mi::AttributeSet attrSet;
        attrSet.createNumericAttribute<int> ( "-t", t );
        attrSet.parse ( arg );
        std::cerr << "-i :" << arg.get<std::string> ( "-i" ) << t << std::endl;
        return 0;
}
