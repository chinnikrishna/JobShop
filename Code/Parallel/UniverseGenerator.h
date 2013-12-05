#ifndef __UNIV_GEN_H__
#define __UNIV_GEN_H__

#include "types.h"

int EvaluateChromosome(unsigned int Jobs, unsigned int Machines,unsigned int ***T,unsigned int ***P1);

int CreateUniverse(int Population, Individual* Universe, unsigned int Jobs, unsigned int Machines);

int PrintIndividual(Individual Ind);

#endif // __UNIV_GEN_H__
