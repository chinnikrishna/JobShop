/*
 Name:          Genetic Algorithm to solve JSS
 Author:        ChinniKrishna Kothapalli
 Email:         kothapal@pdx.edu
 Date:          11/23/13
 Version:       0.1
 Description:   A serial program to solve Job Shop Scheduling problem
 ToDo:*/

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;

//Data Structure for Chromosome
struct Individual{
    string Genome;
    float Fitness;
};
//Class for our Universe
class Universe{
public:
    Universe(size_t Pop);
private:
    vector<Individual> Population;
};
//Constructor for Universe
Universe::Universe(size_t Pop)
    : Population(vector<Individual>(Pop,Individual())) //Initializer list
{

}
static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//Function which generates a random character
char GetRandom(int Position){
    return alphanum[rand() % Position];
}
//******************************************************************************
//                          MAIN
//******************************************************************************
int main()
{
    //Assuming a 3 machines 3 jobs scenario. So chromosome
    int Jobs=4;
    int Machines=3;
    int ChromLength=Jobs*Machines;
    int StringLength=Jobs;
    int Counter[Jobs],i;
    char C;
    char Chromosome[(ChromLength-1)];
    //Seeding
    srand(time(0));
    //Init array
    for(int Cnt=0;Cnt<Jobs;Cnt++)
        Counter[Cnt]=0;
    //Test
    //Fill the array
    for(i=0;i<ChromLength;)
    {
        //Get the Character
        C=GetRandom(StringLength);
        cout<<"Char:"<<C<<endl;
        //Check which character is returend
        for(int j=0;j<StringLength;j++)
        {
            if(C==alphanum[j])
            {
                Counter[j]++;
                cout<<"I am in J "<<j<<" Char:"<<C<<endl;
                if(Counter[j]==Jobs)
                    break;
                else
                {
                    Chromosome[i]=C;
                    cout<<"I:"<<i<<endl;
                    i++;
                }
            }
        }
    }
    Chromosome[ChromLength]='\0';
    cout<<Chromosome<<endl;
    for(int i=0;i<Jobs;i++)
        cout<<Counter[i];

    return 0;
}
