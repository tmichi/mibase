#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <mi/CommandTemplate.hpp>
#include <mi/AttributeSet.hpp>
#include <mi/SystemInfo.hpp>

class ExampleCommand : public mi::CommandTemplate
{
private:
        std::string _input_file;
        std::string _output_file;
public:
        ExampleCommand ( void ) ;
        ~ExampleCommand ( void ) ;
        bool init ( const mi::Argument& arg ) ;
        bool run  ( void );
        bool term ( void );
};

ExampleCommand::ExampleCommand ( void ) : mi::CommandTemplate(  )
{
        mi::AttributeSet &attrSet = this->getAttributeSet();
        attrSet.createStringAttribute( "-i", this->_input_file ).setMandatory();
        attrSet.createStringAttribute( "-o", this->_output_file ).setMandatory();
        return;
}

ExampleCommand::~ExampleCommand ( void )
{
        std::cerr<<"ExampleCommand::~ExampleCommand() was called."<<std::endl;
        std::cerr<<"peak memory : "<<mi::SystemInfo::getPeakMemorySize( mi::MI_KILO_BYTE )<<"[kb]"<<std::endl;
        return;
}


bool
ExampleCommand::init ( const  mi::Argument& arg )
{
        mi::AttributeSet &attrSet = this->getAttributeSet();
        if( !attrSet.parse( arg ) ) {
                attrSet.printError();
                return false;
        }
        attrSet.print();
        return true;
}

bool
ExampleCommand:: run ( void )
{
        std::cerr<<"ExampleCommand::run() was called."<<std::endl;
        return true;
}

bool
ExampleCommand:: term ( void )
{
        std::cerr<<"ExampleCommand::term() was called."<<std::endl;
        return true;
}


int main ( int argc, char** argv )
{
        mi::Argument arg( argc, argv );
        ExampleCommand cmd;
        if ( !cmd.init( arg ) ) {
                std::cerr<<"initalization failed."<<std::endl;
                return -1;
        }
        if ( !cmd.run() ) {
                std::cerr<<"execution failed."<<std::endl;
                return -2;
        }
        if ( !cmd.term() ) {
                std::cerr<<"terminiation failed."<<std::endl;
                return -3;
        }
        return 0;
}
