#include "Operations.h"
int main()
{
    int NumMachines;
    int NumJobs;
    //Read the BenchMark file
    ReadBenchMark("C:\\sample.txt",&NumMachines,&NumJobs);
    //Generate Individual
    GenerateIndividual(NumJobs,NumMachines);
    //ScheduleDecoder();

}
