/*
 Name:          UniverseGenerator.cpp
 Author:        ChinniKrishna Kothapall
 Email:         kothapal@pdx.edu
 Date:          11/20/13
 Version:       0.1
 Description:   Evaluate Individuals by reporting their fitness
 ToDo:*/
//#include "operations.h"

#include <cstring>
#include <iostream>
#include <algorithm>
#include "types.h"
#include "EvaluateIndividual.h"

int EvaluateIndividual(Individual& indv, unsigned int Jobs, unsigned int Machines, unsigned int ***T1,unsigned int ***P1,bool done)
{
    string ind = indv.Chromosome;
    unsigned int i=0;
    unsigned int j=0;
    unsigned int k=0;
    unsigned int start=0;
    //Array to keep track of task
    unsigned int Tnext[Machines];
    unsigned int Snext[Machines];
    unsigned int Jstart[Machines];
    unsigned int Mstart[Machines];
    //Copying Technology and Processing time matrix
    unsigned int **T2 = (*T1);
    unsigned int **P2 = (*P1);
    unsigned int ** T = new unsigned int* [Jobs];
    unsigned int ** P = new unsigned int* [Jobs];

    for(unsigned int a = 0; a < Jobs; a++)
    {
        T[a] = new unsigned int [Machines];
        P[a] = new unsigned int [Machines];
    }
    for(unsigned int a=0;a<Jobs;a++)
    {
        //cout<<endl;
        for(unsigned int b=0;b<Machines;b++)
        {
            T[a][b] = T2[a][b];
            P[a][b] = P2[a][b];
            //cout<<" "<<T[a][b];
        }
    }

    //Solution Matrix
    unsigned char S[Machines][Jobs];
    //Time Matrix
    unsigned int Jstartind[Jobs][Machines];
    //Setting to zero
    for(unsigned int a=0;a<Machines;a++)
    {
        Tnext[a]=0;
        Snext[a]=0;
        Jstart[a]=0;
        Mstart[a]=0;
    }
    //Setting to zero
    for(unsigned int a=0;a<Machines;a++)
    {
        for(unsigned int b=0;b<Jobs;b++)
        {
            S[a][b]=0;
            Jstartind[a][b]=0;
        }
    }
    //Chromosome Evaluation
    for (k = 0; k < ind.length(); k++)
    {
        /*operation sequencing*/
        i = ind[k] - 'A';         // Current Job
        j = T[i][Tnext[i]];       // Machine Name
        //cout<<" I:"<<i<<" J:"<<j<<" P:"<<P[i][j]<<endl;
        S[j][Snext[j]] = i + 'A'; // Current Job on this Machine
        ++Tnext[i];               // Sub task in current job
        ++Snext[j];               // Next job on this machine

        /*semi-active scheduling*/
        start = max(Jstart[i],Mstart[j]);
        Jstart[i] = start + P[i][j];
        Mstart[j] = start + P[i][j];

        //Filling the time matrices
        Jstartind[i][j] = Jstart[i];
    }
    //Assigning fitness
    indv.Fitness=Jstart[0];
    //Printing Solution and Time
    if (done)
    {
        cout << endl;
        cout << "Solution Matrix"<<endl;
        for (unsigned int i = 0; i < Machines; i++)
        {
            cout << "M" << i + 1 << "\t";
            for(unsigned int j = 0; j < Jobs; j++)
            {
                cout << S[i][j]<< "\t";
            }
            cout << endl;
        }
        cout<<endl<<endl;
        cout<<"JOB TIMES:"<<endl;
        for (unsigned int i = 0; i < Jobs; i++)
        {
            cout << "J" << i + 1 << "\t";
            for(unsigned int j = 0; j < Machines; j++)
            {
                cout << Jstartind[i][j] << "\t";
            }
            cout << endl;
        }

    }

    #if 0
    {
         //Gnatt-Chart
        cout<<endl;
        cout<<"Gnatt-Chart"<<endl;
        int TaskNumber=0;
        int lastMachine=0;
        int lastTask=0;
        string GnattChart[Machines];
        for(int  a=0;a<Machines;a++)
        {
            cout << "M" << a + 1 << "\t";
            for(int  b=0;b<Jobs;b++)
            {
                int  SolutionTemp=S[a][b]-'A';
                for(int c=0;c<Machines;c++)
                    if(T[SolutionTemp][c]==a)
                        TaskNumber=c;
                int SlotPosition=(((Jstartind[SolutionTemp][TaskNumber])-(Jstartind[lastMachine][lastTask])));
                if(SlotPosition<0)
                    SlotPosition=-SlotPosition;
                if(SlotPosition<=1)
                    cout<<string(P[SolutionTemp][TaskNumber],S[a][b]);
                if(SlotPosition>1)
                {
                    cout<<string(SlotPosition,'-');
                    cout<<string(P[SolutionTemp][TaskNumber],S[a][b]);
                }
                lastMachine=SolutionTemp;
                lastTask=TaskNumber;
            }
            cout<<endl;
        }

    }
    #endif
    return 0;
}

int SortPopulation(Individual Popu[],int population,Individual *temp)
{
    //cout<<"Init"<<endl;
    for(int i=0;i<population;i++)
    {
        temp[i].Fitness=Popu[i].Fitness;
        temp[i].Chromosome=Popu[i].Chromosome;
        //cout<<"Chromosome:"<<temp[i].Chromosome<<" Fitness:"<<temp[i].Fitness<<endl;
    }
    sort(temp, temp+population, [](Individual const &a, Individual const &b){ return a.Fitness < b.Fitness; });
    for(int i=0;i<population;i++)
        temp[i].Fitness=temp[i].Fitness/temp[population-1].Fitness;

    #if 0
    cout<<"Sorted"<<endl;
    for(int i=0;i<population;i++)
    {
        cout<<"Chromosome:"<<temp[i].Chromosome<<" Fitness:"<<temp[i].Fitness<<endl;
    }
    #endif
}


/*int PrintGnattChart()
{
    //Gnatt-Chart
    cout<<endl;
    cout<<"Gnatt-Chart"<<endl;
    int TaskNumber=0;
    int lastMachine=0;
    int lastTask=0;
    string GnattChart[MACHINES];
    for(int  a=0;a<MACHINES;a++)
    {
        cout << "M" << a + 1 << "\t"<<endl;
        for(int  b=0;b<Jobs;b++)
        {
            int  SolutionTemp=S[a][b]-'A';
            for(int c=0;c<MACHINES;c++)
                if(T[SolutionTemp][c]==a)
                    TaskNumber=c;
            int SlotPosition=(((Jstartind[SolutionTemp][TaskNumber])-(Jstartind[lastMachine][lastTask])));
            if(SlotPosition<0)
                SlotPosition=-SlotPosition;
            if(SlotPosition<=1)
                cout<<string(P[SolutionTemp][TaskNumber],S[a][b]);
            if(SlotPosition>1)
            {
                cout<<string(SlotPosition,'-');
                cout<<string(P[SolutionTemp][TaskNumber],S[a][b]);
            }
            lastMachine=SolutionTemp;
            lastTask=TaskNumber;
        }
        cout<<endl;
    }
}*/

