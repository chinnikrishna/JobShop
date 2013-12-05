#include <iostream>
#include <pthread.h>

using namespace std;

int main(int argc,char** argv)
{
    //Checking for commandline arguments
    if(argc<4)
    {
        cerr<<"Usage: " << argv[0] <<" -BenchmarkName -Population -Threads " <<endl;
    	exit(1);
    }
}
