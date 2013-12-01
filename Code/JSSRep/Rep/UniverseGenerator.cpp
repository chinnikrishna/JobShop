/*
 Name:          UniverseGenerator.cpp
 Author:        ChinniKrishna Kothapalli
 Email:         kothapal@pdx.edu
 Date:          11/08/13
 Version:       0.1
 Description:   Generates universe with required number of individuals. Required number of individuals are mentioned with population parameter
 ToDo:*/

#include "Operations.h"


//Gene Codebase
static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";



//Function to Generate Random Character
char GetRandomChar(int Position)
{
    return alphanum[rand() % Position];
}
//Print Individual
int PrintIndividual(Individual Ind[],int Population)
{
    for(int i=0;i<Population;i++)
    {
        cout<<"Chromosome "<<i<<":"<<Ind[i].Chromosome;
        cout<<"\tFitness "<<i<<":"<<Ind[i].Fitness<<endl;
    }
    return 0;
}
//Creates Universe with population as parameter
Individual CreateUniverse(int Population)
{
    int NumMachines;
    int NumJobs;
    //Seeding the Random number generator
    srand(time(0));
    //Generate a universe of population
    Individual Universe[Population];
    //Read the BenchMark file
    ReadBenchMark("C:\\sample.txt",&NumMachines,&NumJobs);
    for(int i=0;i<Population;i++)
    {
        Universe[i].Chromosome=GenerateChromosome(NumJobs,NumMachines);
        Universe[i].Fitness=0.0;

    }
    PrintIndividual(Universe,Population);
}

//Generates a random individual by permutations with repetations
string GenerateChromosome(int Jobs,int Machines)
{
    //Variables
    int ChromosomeLength=Jobs*Machines;         //Length of Chromosome
    int Position=Jobs;                          //Position for alphanum
    int Counter[Jobs];                          //Counter to enforce numbering
    char Test;                                  //Storage for the char returned by GetRandomChar
    string Chromosome;        //Actual Chromosome generated
    int i;                                      //General purpose counter



    //Initialize the Counter Array
    for(int Cnt=0;Cnt<Jobs;Cnt++)
        Counter[Cnt]=0;

    //Filling the Chromosome with correct number of genes
    for(i=0;i<ChromosomeLength;)
    {
        //Get the Character
        Test=GetRandomChar(Position);

        //Test to know if chromosome is filled with equal number of genes
        for(int j=0;j<Position;j++)
        {
            if(Test==alphanum[j])
            {
                if(Counter[j]<Machines)
                {
                    Counter[j]++;
                    Chromosome.append(string(1,Test));
                    i++;
                    break;
                }
                else
                    break;
            }
        }
    }
    //Null terminate the string
    Chromosome[ChromosomeLength]='\0';

    #ifdef DEBUG
    cout<<Chromosome<<endl;
    for(int i=0;i<Jobs;i++)
        cout<<Counter[i];
    #endif
    return Chromosome;
}
/*//Validates if the randomly generated individual follows the technological process
int ScheduleDecoder(string Chromosome)
{
    int T1[3][4]={{1,3,2,4},{1,4,2,3},{3,2,4,1}};

    return 0;
}*/
