#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <mi/CommandTemplate.hpp>

class ExampleCommand : public mi::CommandTemplate
{
private:
        std::string _input_file;
        std::string _output_file;
        double      _param0;
public:
        ExampleCommand ( void ) ;
        ~ExampleCommand ( void ) ;
        bool init ( const mi::Argument& arg ) ;
        bool run  ( void );
        bool term ( void );
};

ExampleCommand::ExampleCommand ( void ) : mi::CommandTemplate(  )
{
        mi::AttributeSet& attrSet = this->getAttributeSet();
        attrSet.createStringAttribute ( "-i", this->_input_file, "input file" ).setMandatory();
        attrSet.createStringAttribute ( "-o", this->_output_file, "output file" ).setMandatory();
        attrSet.createNumericAttribute ( "-p", this->_param0, "value" ).setMin ( -10 ).setMax ( 10 ).setDefaultValue ( 0 );
        return;
}

ExampleCommand::~ExampleCommand ( void )
{
        std::cerr << "ExampleCommand::~ExampleCommand() was called." << std::endl;
        return;
}


bool
ExampleCommand::init ( const  mi::Argument& arg )
{
        mi::AttributeSet& attrSet = this->getAttributeSet();

        if ( !attrSet.parse ( arg ) ) {
                return false;
        }

        attrSet.print();
        return true;
}

bool
ExampleCommand:: run ( void )
{
        std::cerr << "ExampleCommand::run() was called." << std::endl;
        return true;
}

bool
ExampleCommand:: term ( void )
{
        std::cerr << "ExampleCommand::term() was called." << std::endl;
        return true;
}


int main ( int argc, char** argv )
{
        mi::Argument arg ( argc, argv );
        ExampleCommand cmd;
	return  mi::CommandTemplate::execute ( cmd, arg );

}
