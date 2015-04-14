#include <mi/Thread.hpp>
#include <iostream>
#include <cstdlib>
mi::Thread thread;

typedef struct _argument {
        int a;
        double b;
        double* sum;
} argument;


void run_child( int a, double b, double* sum )
{
        thread.startCriticalSection();
        std::cerr<<a<<" : "<<b<<std::endl;
        *sum += b;
        thread.endCriticalSection();
}
static ThreadResult launch( void* arg )
{
        argument* arg0 = ( argument* )( arg );
        int a = arg0->a;
        double b = arg0->b;
        double *sum = arg0->sum;
        run_child( a, b, sum );
        return 0;
}
void run_sample ( int nthread )
{
        argument *args = new argument [ nthread ];
        double sum = 0.0;
        for ( int i = 0 ; i < nthread ; ++i ) {
                args[i].a = i;
                args[i].b = rand() % 1000 * 0.01;
                args[i].sum = &sum;

                thread.createThread( launch, &args[i] );
        }
        thread.waitAll();
        thread.closeAll();
        delete[] args;

        std::cerr<<"total : "<<sum<<std::endl;
        return;
}



int main ( int argc, char** argv )
{
        const int nthread = 20;
        run_sample( nthread ) ;
        return 0;
}
