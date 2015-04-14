#include <string>
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
        this->getTimer().start( "total" );
        mi::AttributeSet &attrSet = this->getAttributeSet();
        attrSet.createStringAttribute( "-i", this->_input_file ).setMandatory();
        attrSet.createStringAttribute( "-o", this->_output_file ).setMandatory();
        return;
}

ExampleCommand::~ExampleCommand ( void )
{
        this->getTimer().end( "total" );
        std::cout<<"ExampleCommand::~ExampleCommand() was called."<<std::endl;
        return;
}


bool
ExampleCommand::init ( const  mi::Argument& arg )
{
        this->getTimer().start( "init" );
        mi::AttributeSet &attrSet = this->getAttributeSet();
        if( !attrSet.parse( arg ) ) {
                attrSet.printError();
                return false;
        }
        attrSet.print();
        this->getTimer().end( "init" );
        return true;
}

bool
ExampleCommand:: run ( void )
{
        this->getTimer().start( "run" );
        std::cerr<<"ExampleCommand::run() was called."<<std::endl;
	std::vector<char> v(100000000, 0);
        this->getTimer().end( "run" );
        return true;
}

bool
ExampleCommand:: term ( void )
{
        this->getTimer().start( "term" );
        std::cerr<<"ExampleCommand::term() was called."<<std::endl;
        this->getTimer().end( "term" );
        return true;
}


int main ( int argc, char** argv )
{
        mi::Argument arg( argc, argv );
        ExampleCommand cmd;
        return mi::CommandTemplate::execute( cmd,arg );

}

