#include <mi/Routine.hpp>
#include <iostream>
#include <sstream>
/*
  The result will be : 
  $ ./samples/routine1 
  applying test routine ...  failed.
  Invalid calculation
  $
 */
class TestRoutine: public mi::Routine {
private:
	const int& _a;
	int& _b;
public:
	TestRoutine ( const int& aa, int& bb) : mi::Routine("test") , _a(aa), _b(bb) {
		return;
	}

	bool run_main_routine ( void ) {
		this->_b = this->_a * 100;
		this->set_failed();
		this->stream() << "Invalid calculation"<<std::endl;
		return this->check();
	}
};


int main ( int argc, char** argv ) {
	int a = 20;
	int b;
	mi::Routine::setDebugModeOn();
	if ( !mi::Routine::run(	TestRoutine(a, b).getInstance() ) ) return 0;
	//TestRoutine routine (a, b);
//	if ( !mi::Routine::run(	routine ) ) return 0;

	std::cerr<<"invalid"<<std::endl;
	return -1;
}
