#include <mi/Routine.hpp>
#include <iostream>
#include <memory>
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
		return this->check();
	}
};


int main ( int argc, char** argv ) {
	int a = 20;
	int b;
//	if ( !mi::Routine::run(TestRoutine(a, b).getInstance() ) ) return -1;
	if ( !mi::Routine::run(TestRoutine(a, b).getInstance() ) ) return -1;
	//TestRoutine routine (a, b);
	//if ( !mi::Routine::run(routine) ) return -1;
	std::cerr<<b<<std::endl;
	return 0;
}
