/*
 Name:          Operations.h
 Author:        ChinniKrishna Kothapalli
 Email:         kothapal@pdx.edu
 Date:          11/08/13
 Version:       0.1
 Description:   Header file which has all the prototypes of the fucntions
 ToDo:*/
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

#ifndef FILEOPS_H_INCLUDED
#define FILEOPS_H_INCLUDED
//#define DEBUG 1
//Prototypes
int ReadBenchMark(string FileName,int *Machines,int *Jobs); //Defined in FileOps.cpp
string GenerateChromosome(int Jobs,int Machines);              //Defined in IndividualGenerator.cpp
int CreateUniverse(int Population);



#endif // FILEOPS_H_INCLUDED
