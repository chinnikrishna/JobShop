#include <iostream>
#include <time>
#include <assert>
#include <pthread.h>
using namespace std;

//Technology Matrix
extern unsigned int **T;
//Processing Time Matrix
extern unsigned int **P;
struct timespec startTime;
struct timespec endTime;
//Main Function
int main(int argc,char** argv)
{
    //Checking for commandline arguments
    if(argc<4)
    {
        cerr<<"Usage: " << argv[0] <<" -BenchmarkName -Population -Threads " <<endl;
		exit(1);
    }
	//Start Clock
    clock_gettime(CLOCK_REALTIME, &StartTime);
    //1. Reading Benchmarks
    FILE* fp = fopen(argv[1],"r+");
    ReadBenchMark(fp, &NumJobs, &NumMachines);
}
