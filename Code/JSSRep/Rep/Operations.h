#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#ifndef FILEOPS_H_INCLUDED
#define FILEOPS_H_INCLUDED
int ReadBenchMark(string FileName,int *Machines,int *Jobs); //Defined in FileOps.cpp
int GenerateIndividual(int Jobs,int Machines);              //Defined in IndividualGenerator.cpp
int ScheduleDecoder();                 //Defined in IndividualGenerator.cpp
//int GeneratePopulation(int Population);                     //Defined in IndividualGenerator.cpp
#endif // FILEOPS_H_INCLUDED
