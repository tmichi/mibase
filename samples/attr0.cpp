#include <mi/AttributeSet.hpp>
#include <mi/Argument.hpp>
#include <iostream>
#include <string>
int main ( int argc, char** argv )
{
        std::string stri;
        double v1;
        int v2;

        mi::Argument arg ( argc, argv );
        mi::AttributeSet attrSet;
        attrSet.createStringAttribute ( "-i", stri ).setMandatory();
        attrSet.createNumericAttribute<double> ( "-v1", v1 ).setMin ( 20 ).setMax ( 30 ).setDefaultValue ( 25 );
        attrSet.createNumericAttribute<int> ( "-v2", v2 ).setMandatory().setMin ( 20 ).setMax ( 30 ).setOutRangeRejected();

        if ( !attrSet.parse ( arg ) ) {
                return EXIT_FAILURE;
        }

        std::cerr << " -i : " << stri << "\n";
        std::cerr << " -v1 : " << v1 << "\n";
        std::cerr << " -v2 : " << v2 << "\n";

        return EXIT_SUCCESS;
}
