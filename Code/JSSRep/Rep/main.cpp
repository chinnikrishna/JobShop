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
#include "types.h"
//#include "Operations.h"
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

#define CROSSOVER_PART	(0.4)
#define __debug__

#define CROSSOVER_PERC  (0.4)
#define NUM_GENERATIONS (100)
int main(int argc,char** argv)
{
    //Parsing command line parameters
    if(argc < 3)
    {
        cerr<<"Usage: " << argv[0] <<" -BenchmarkName -Population" <<endl;
        return 0;
    }

    //Create Universe
    unsigned int population = 10;//atoi(argv[2]);
    unsigned int len_crossover;


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
        EvaluateIndividual(universe[i],NumJobs, NumMachines,&T,&P);


    //Sort the population according to their fitness and fill it in SortedPopulation
    SortPopulation(universe,population,SortedPopulation);
    cout<<"Hero was:"<<SortedPopulation[0].Chromosome<<" whose fitness is "<<SortedPopulation[0].Fitness<<endl;

    //Evolving
    for(int GenCounter=0;GenCounter<NUM_GENERATIONS;GenCounter++)
    {
        CreateNewPopulation(SortedPopulation,population,NewPopulation,NumJobs,NumMachines);
        for(unsigned int i = 0; i < population; i++)
            EvaluateIndividual(NewPopulation[i],NumJobs, NumMachines,&T,&P);
        SortPopulation(NewPopulation,population,SortedPopulation);
        cout<<"Hero is:"<<SortedPopulation[0].Chromosome<<" whose fitness is "<<SortedPopulation[0].Fitness<<endl;

        //cout<<"New POP"<<endl;
        //for(int i=0;i<population;i++)
            //cout<<"Chromosome:"<<SortedPopulation[i].Chromosome<<" Fitness:"<<SortedPopulation[i].Fitness<<endl;

    }




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
