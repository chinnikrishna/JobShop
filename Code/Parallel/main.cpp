//Library Includes
#include <iostream>
#include <ctime>
#include <cassert>
#include <pthread.h>
//File Includes
#include "types.h"
#include "crossover.h"
#include "FileOps.h"
#include "EvaluateIndividual.h"
#include "UniverseGenerator.h"
using namespace std;
//Technology Matrix
extern unsigned int **T;
//Processing Time Matrix
extern unsigned int **P;
// Number of Jobs
unsigned int NumJobs;
// Number of Machines
unsigned int NumMachines;
//Time Variables
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
    clock_gettime(CLOCK_REALTIME, &startTime);
    //Reading Benchmarks
    FILE* fp = fopen(argv[1],"r+");
    ReadBenchMark(fp, &NumJobs, &NumMachines);
	//End Clock
	clock_gettime(CLOCK_REALTIME, &endTime);
	//Reporting Results
	unsigned long long int runtime = 1000000000 * (endTime.tv_sec - startTime.tv_sec) + endTime.tv_nsec - startTime.tv_nsec;
  	printf("(%d.%09lld sec)\n", runtime / 1000000000, runtime % 1000000000);
}
