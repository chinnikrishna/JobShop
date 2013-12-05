/*
 Name:          main.cpp
 Author:        ChinniKrishna Kothapalli
 Email:         kothapal@pdx.edu
 Date:          11/08/13
 Version:       0.1
 Description:   Genetic Algorithm to solve Job Shop Scheduling
 ToDo:*/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "types.h"
#include "crossover.h"
#include "FileOps.h"
#include "EvaluateIndividual.h"
#include "UniverseGenerator.h"

// Technology matrix
unsigned int **T;

// Processing Time matrix
unsigned int **P;

// Number of Jobs
unsigned int NumJobs;

// Number of Machines
unsigned int NumMachines;

struct timespec StartTime;                  //Used by gettime
struct timespec EndTime;

#define CROSSOVER_PART	(0.4)
#define __debug__

#define CROSSOVER_PERC  (0.4)
#define NUM_GENERATIONS (10)
int main(int argc,char** argv)
{
    //Parsing command line parameters
    if(argc < 3)
    {
        cerr<<"Usage: " << argv[0] <<" -BenchmarkName -Population" <<endl;
        return 0;
    }
    //Seed the randomizer
    srand(0);
    bool done=false;
    //Create Universe
    unsigned int population = atoi(argv[2]);
    unsigned int len_crossover;

    //Start Clock
    clock_gettime(CLOCK_REALTIME, &StartTime);
    //1. Reading Benchmarks
    FILE* fp = fopen(argv[1],"r+");
    ReadBenchMark(fp, &NumJobs, &NumMachines);

    //2. Create the universe
    Individual* universe = new Individual[population];
    Individual* SortedPopulation = new Individual[population];
    Individual* NewPopulation = new Individual[population];

    //Fill the universe with individuals
    CreateUniverse(population, universe,NumJobs,NumMachines);

    //Evaluate the fitness of each individual
    for(unsigned int i = 0; i < population; i++)
        EvaluateIndividual(universe[i],NumJobs, NumMachines,&T,&P,done);


    //Sort the population according to their fitness and fill it in SortedPopulation
    SortPopulation(universe,population,SortedPopulation);
    cout<<"Hero was:"<<SortedPopulation[0].Chromosome<<" whose fitness is "<<SortedPopulation[0].Fitness<<endl;




    float nfit=1.0;
    float tfit=SortedPopulation[0].Fitness;

    while(1)
    {
        CreateNewPopulation(SortedPopulation,population,NewPopulation,NumJobs,NumMachines);
         for(unsigned int i = 0; i < population; i++)
            EvaluateIndividual(NewPopulation[i],NumJobs, NumMachines,&T,&P,done);
        SortPopulation(NewPopulation,population,SortedPopulation);
        nfit=SortedPopulation[0].Fitness;
        if(nfit<tfit)
        {
            cout<<"Hero is:"<<SortedPopulation[0].Chromosome<<" whose fitness is "<<SortedPopulation[0].Fitness<<endl;
            done=true;
            EvaluateIndividual(SortedPopulation[0],NumJobs, NumMachines,&T,&P,done);
            break;
        }

    }
    clock_gettime(CLOCK_REALTIME, &EndTime);

	//Reporting Results
	unsigned long long int runtime = 1000000000 * (EndTime.tv_sec - StartTime.tv_sec) + EndTime.tv_nsec - StartTime.tv_nsec;
  	printf("(%d.%09lld sec)\n", runtime / 1000000000, runtime % 1000000000);



    //Cleanup
    unsigned int i;
    // Delete allocated memory
    if(universe)
        delete[] universe;

    if(T)
        for(i = 0; i < NumMachines; i++)
            delete[] T[i];

    if(P)
        for(i = 0; i < NumMachines; i++)
            delete[] P[i];


}
