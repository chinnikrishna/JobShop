#ifndef __CROSSOVER_H__
#define __CROSSOVER_H__

#include <string>
#include "types.h"

int CreateNewPopulation(Individual OldPop[],int population,Individual *NewPop,int NumJobs,int NumMachines);
string CrossOver(const string& parent, const string& donor, unsigned int len_crossover,
                 unsigned int numJobs, unsigned int numMachines);
string RouletteSelection(int TotalFitness,Individual *Popu,int Population);

unsigned int GetInsertionPoint(const string& parent, unsigned int* parentPos,
                               unsigned char cutChrStartGene, unsigned int cutChrStartGenePos);

void GetCombinedChromosome(const string& parent, const string& donor, unsigned int len_crossover,
                           gene* combined, unsigned int numMachines);

string RepairCombinedChromosome(gene* combinedChromosome, unsigned int len,unsigned int numJobs,
                                unsigned int len_crossover);

bool validateChromosome(const string& chr, unsigned int numJobs, unsigned int numMachines);

#endif // __CROSSOVER_H__
