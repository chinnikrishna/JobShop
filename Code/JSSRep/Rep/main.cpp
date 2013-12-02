/*
 Name:          main.cpp
 Author:        ChinniKrishna Kothapalli
 Email:         kothapal@pdx.edu
 Date:          11/08/13
 Version:       0.1
 Description:   Genetic Algorithm to solve Job Shop Scheduling
 ToDo:*/
#include "Operations.h"

// Technology matrix
unsigned int **T;

// Processing Time matrix
unsigned int **P;

// Number of Jobs
unsigned int NumJobs;

// Number of Machines
unsigned int NumMachines;


int main()
{
    //Create Universe
    unsigned int population = 10;
    //Reading Benchmarks
    FILE* fp = fopen("C:\\Benchmark\\sample.txt","r+");
    ReadBenchMark(fp, &NumJobs, &NumMachines);
    // Create the universe
    Individual* universe = new Individual[population];
    //Fill the universe with individuals
    CreateUniverse(population, universe,NumJobs,NumMachines);
    //EvaluatePopulation
    EvaluateChromosome(NumJobs, NumMachines,&T,&P);

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
