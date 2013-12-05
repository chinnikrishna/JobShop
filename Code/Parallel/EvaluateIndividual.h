#ifndef __EVAL_IND_H__
#define __EVAL_IND_H__

#include <string>
#include "types.h"
string GenerateChromosome(int Jobs,int Machines);
int SortPopulation(Individual Popu[],int population,Individual *temp);

int EvaluateIndividual(Individual& indv,unsigned int Jobs, unsigned int Machines,unsigned int ***T,unsigned int ***P1,bool done);
#endif // __EVAL_IND_H__
