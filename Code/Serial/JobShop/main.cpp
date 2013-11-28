/*
 Name:          Genetic Algorithm to solve JSS
 Author:        ChinniKrishna Kothapalli
 Email:         kothapal@pdx.edu
 Date:          11/23/13
 Version:       0.1
 Description:   A serial program to solve Job Shop Scheduling problem
 ToDo:*/

//Headers
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <cstring>

//Defines
#define CROSSOVER_RATE      0.8
#define MUTATION_RATE       0.4
#define POPULATION          100
#define GENERATIONS         300
#define PERFECT_FITNESS     1
//Namespaces
using namespace std;

//Data Structure for Chromosome
struct Individual
{
    string Genome;
    float Fitness;
};
//Class for our Universe
class Universe
{
public:
    Universe(size_t Pop,string &InitGene);
    void MeasureFitness(){};
    void OrderResults(void);
    void Reproduce(float CR) {}
    void PrintResults(void);
    void Mutate(float MR) {}
private:
    vector<Individual> Population;
};
//Constructor for Universe
Universe::Universe(size_t Pop,string &InitGene)
    : Population(vector<Individual>(Pop,Individual())) //Initializer list
{
    //At this point all the individuals have a 0.0 fitness and an empty genome string.
    for(auto &ind:Population){
        ind.Genome=InitGene;
    }
}
//OrderResults method
void Universe::OrderResults()
{
    sort(Population.begin(),Population.end(),
        [](const Individual &a, const Individual &b)
        {
            return a.Fitness > b.Fitness;
        });
    //Check if we evolved a perfect solution
    if(Population[0].Fitness>=PERFECT_FITNESS)
    {
        cout << "Found the best schedule"<<endl;
        cout << "Genome=" << Population[0].Genome<<endl;
        exit(0);
    }
}
//PrintResults Method
void Universe::PrintResults(void)
{
    auto &ind= Population[0];
    cout << "Best Genome (" << ind.Fitness<< ")=\'"<<ind.Genome<<"\'"<<endl;
}
//Command line parse
struct CmdLineParameters
{
    CmdLineParameters(void):
        MR(MUTATION_RATE),      //-M
        Pop(POPULATION),        //-P
        Gen(GENERATIONS),      //-G
        InitGene("Chinni")
    {}
    float MR;
    size_t Pop;
    int Gen;
    string InitGene;
    void ParseCmdLine(int argc,char **argv);
private:
    template <typename T>
    void getArg(T *pRetVal,int &i,int argc,char **argv)
    {
        if(argv[i][2]!='\0'){
            istringstream(&argv[i][2]) >> *pRetVal;
            return;
        } else if (i < argc - 1){
            istringstream(argv[++i]) >> *pRetVal;
            return;
        }
        cout << "gajss [-P Population] [-M MutationRate] [-G Generations]"<<endl;
        exit(1);
    }
};

//Above this line is about defining class Universe
//******************************************************************************
//Below this line is aboute using class Universe

void CmdLineParameters::ParseCmdLine(int argc,char **argv)
{
    for(int i=1;i<argc;++i){
        if(strncmp(argv[i],"-M",2)==0){
            getArg(&MR,i,argc,argv);
        } else if (strncmp(argv[i],"-P",2)==0){
            getArg(&Pop,i,argc,argv);
        } else if(strncmp(argv[i],"-G",2)==0) {
            getArg(&Gen,i,argc,argv);
        } else {
            InitGene=string(argv[i]);
        }
    }
}
//Main Starts here
int main(int argc, char **argv)
{
    CmdLineParameters args;
    args.ParseCmdLine(argc,argv);
    //Make a universe with a bunch of individuals
    Universe MyWorld(args.Pop,args.InitGene);
    //Evolve the population
    for(size_t GenNum=0;(GenNum<=args.Gen);++GenNum)
    {
        cout<< "\nGeneration" << GenNum <<endl;
        MyWorld.MeasureFitness();
        MyWorld.OrderResults();
        MyWorld.Reproduce(CROSSOVER_RATE);
        MyWorld.Mutate(MUTATION_RATE);
        MyWorld.PrintResults();
    }
}
