#include <mi/Thread.hpp>
#include <iostream>
#include <cstdlib>
class ThreadSample
{
private:
        typedef struct _argument {
                ThreadSample* instance;
                int a;
                double b;
        } argument;
private:
        mi::Thread _thread;
        int _nthread;
        double _sum;
public :
        explicit ThreadSample ( const int nthread = 1 ) : _nthread ( nthread )
        {
                this->_sum = 0;
                return;

        }
        void run ( void )
        {
                argument* args = new argument [ this->_nthread ];

                for ( int i = 0 ; i < this->_nthread ; ++i ) {
                        args[i].instance = this;
                        args[i].a = i;
                        args[i].b = rand() % 1000 * 0.01;

                        this->_thread.createThread ( ThreadSample::child_thread, &args[i] );
                }

                this->_thread.waitAll();
                this->_thread.closeAll();
                delete[] args;
                std::cerr << "total : " << this->_sum << std::endl;
                return;
        }
private:
        static ThreadResult child_thread ( void* arg )
        {
                argument* arg0 = ( argument* ) ( arg );
                ThreadSample* instance = arg0->instance;
                int a = arg0->a;
                double b = arg0->b;
                instance->run_child ( a, b );
                return 0;
        }

        void run_child ( int a, double b )
        {
                this->_thread.startCriticalSection();
                std::cerr << a << " : " << b << std::endl;
                this->_sum += b;
                this->_thread.endCriticalSection();
        }
};

int main ( int argc, char** argv )
{
        const int nthread = 20;
        ThreadSample sample ( nthread );
        sample.run();
        return 0;
}
