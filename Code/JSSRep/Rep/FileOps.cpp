#include "Operations.h"

// Technology matrix
extern unsigned int **T;

// Processing times matrix
extern unsigned int **P;

int ReadBenchMark(FILE* fp, unsigned int* jobs, unsigned int* machines)
{

    // Loop counters
    unsigned int i = 0;

    // Number of Jobs
    unsigned int numJobs;

    // Number of Machines
    unsigned int numMachines;

    // Line buffer for per line file read
    char line[1024];

    // Pointer to characters inside the line
    char * pline = &line[0];

    // Job count AKA line counter
    unsigned int jobCount = 0;

    // Number of characters read by sscanf
    unsigned int ch;

    // Argument checks
    if(!fp || !jobs || !machines)
    {
        cout<<"FILE NOT FOUND"<<endl;
        return 0;
    }

    // Read the number of machines and number of jobs
    fscanf(fp,"%d %d",&numJobs,&numMachines);
    *jobs = numJobs;
    *machines = numMachines;

    // Allocate memory for Technology Order matrix
    T = new unsigned int* [numJobs];
    for(i = 0; i < numJobs; i++)
    {
        T[i] = new unsigned int[numMachines];
    }

    // Allocate memory for Processing Time matrix
    P = new unsigned int* [numJobs];
    for(i = 0; i < numJobs; i++)
    {
        P[i] = new unsigned int[numMachines];
    }

    // Read the file linewise
    while(fgets(line,sizeof(line),fp))
    {
       pline = &line[0];

       // Skip line endings
       if(line[0] == '\n')
            continue;

       // Parse the line into format {Machine Name, Task Time}
       // Remember: Number of tasks = number of machines!
       for(i = 0; i < numMachines; i++)
       {
           sscanf(pline,"%d %d%n",&T[jobCount][i], &P[jobCount][i], &ch);
           pline += ch;
       }

       // Increment Line count AKA job count
       jobCount++;
    }

    return 1;

}

