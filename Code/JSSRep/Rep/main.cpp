/*
 Name:          main.cpp
 Author:        ChinniKrishna Kothapalli
 Email:         kothapal@pdx.edu
 Date:          11/08/13
 Version:       0.1
 Description:   Genetic Algorithm to solve Job Shop Scheduling
 ToDo:*/
#include "Operations.h"
int main()
{
    //Create Universe
    unsigned int population = 10;
    unsigned int NumMachines;
    unsigned int NumJobs;

    // Create the universe
    Individual* universe = new Individual[population];

    ReadBenchMark("C:\\sample.txt",&NumMachines,&NumJobs);
    CreateUniverse(population, universe,NumJobs,NumMachines);
    EvaluateChromosome(NumJobs, NumMachines);


    if(universe)
        delete[] universe;

}
