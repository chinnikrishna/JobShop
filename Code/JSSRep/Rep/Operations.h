/*
 Name:          Operations.h
 Author:        ChinniKrishna Kothapalli
 Email:         kothapal@pdx.edu
 Date:          11/08/13
 Version:       0.1
 Description:   Header file which has all the prototypes of the fucntions
 ToDo:*/
 #include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

#ifndef FILEOPS_H_INCLUDED
#define FILEOPS_H_INCLUDED
//#define DEBUG 1


//Data Structure for Individual
struct Individual
{
    string Chromosome;
    float Fitness;
};
//Prototypes
string GenerateChromosome(int Jobs,int Machines);              //Defined in IndividualGenerator.cpp
int CreateUniverse(int Population, Individual* Universe, unsigned int Jobs, unsigned int Machines);
int PrintIndividual(Individual Ind);
int EvaluateChromosome(unsigned int Jobs, unsigned int Machines,unsigned int ***T,unsigned int ***P1);
int ReadBenchMark(FILE* fp, unsigned int* jobs, unsigned int* machines);

#endif // FILEOPS_H_INCLUDED
