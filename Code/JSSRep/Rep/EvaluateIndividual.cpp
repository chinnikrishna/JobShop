/*
 Name:          UniverseGenerator.cpp
 Author:        ChinniKrishna Kothapall
 Email:         kothapal@pdx.edu
 Date:          11/20/13
 Version:       0.1
 Description:   Evaluate Individuals by reporting their fitness
 ToDo:*/
#include "operations.h"


int EvaluateChromosome( unsigned int Jobs, unsigned int Machines)
{

    int i = 0;
    int j = 0;
    int k = 0;
    int start = 0;

    #define JOBS 4
    #define MACHINES 4
    unsigned int T[JOBS][MACHINES] = {{0, 2, 1, 3},
                            {0, 3, 1, 2},
                            {2, 1, 3, 0},
                            };

    unsigned int P[JOBS][MACHINES] = {{0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0}};

    unsigned char S[MACHINES][JOBS] = {{0, 0, 0},
                            {0, 0, 0},
                            {0, 0, 0},
                            {0, 0, 0}};

    char ind[] = "CBADCDADCABB";
    unsigned char *str;

    unsigned int Tnext[JOBS] = {0, 0, 0};
    unsigned int Snext[JOBS] = {0, 0, 0};
    unsigned int Jstart[JOBS] = {0, 0, 0};
    unsigned int Mstart[JOBS] = {0, 0, 0};

    cout << "Length of chromosome" << strlen(ind);
    for (k = 0; k < strlen(ind); k++)
    {
        /*operation sequencing*/
        i = ind[k] - 'A';
        j = T[i][Tnext[i]];
        S[j][Snext[j]] = i + 'A';

        ++Tnext[i];
        ++Snext[j];

        /*semi-active scheduling*/
        start = max(Jstart[i],Mstart[j]);
        Jstart[i] = start + P[i][j];
        Mstart[j] = start + P[i][j];
    }

    cout << endl;
    for (i = 0; i < MACHINES; i++)
    {
        cout << "M" << i + 1 << "\t";
        for(j = 0; j < JOBS; j++)
        {
            cout << S[i][j] << "\t";
        }
        cout << endl;
    }


    return 0;
}
