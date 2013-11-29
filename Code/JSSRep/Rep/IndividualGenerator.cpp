#include "Operations.h"

static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


//Function to Generate Random Character
char GetRandomChar(int Position)
{
    return alphanum[rand() % Position];
}
//Jobs not less than machines
int GenerateIndividual(int Jobs,int Machines)
{
    int ChromosomeLength=Jobs*Machines;
    int Position=Jobs;                      //Position for alphanum
    int Counter[Jobs];                       //Counter to enforce numbering
    char Test;                              //Storage for the char returned by GetRandomChar
    char Chromosome[ChromosomeLength-1];    //Actual Chromosome generated
    int i;
    //Seeding the Random number generator
    srand(time(0));
    //Initialize the Counter Array
    for(int Cnt=0;Cnt<Jobs;Cnt++)
        Counter[Cnt]=0;
    //Filling the Chromosome with correct number of genes
    for(i=0;i<ChromosomeLength;)
    {
        //Get the Character
        Test=GetRandomChar(Position);
        //Check if the Character returned is as per the rules
        for(int j=0;j<Position;j++)
        {
            if(Test==alphanum[j])
            {
                if(Counter[j]<Machines)
                {
                    Counter[j]++;
                    Chromosome[i]=Test;
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
    cout<<Chromosome<<endl;
    //Debug
    for(int i=0;i<Jobs;i++)
        cout<<Counter[i];
    return 0;
}
//Validates if the randomly generated individual follows the technological process
int ScheduleDecoder()
{
    int T[3][4]={{1,3,2,4},{1,4,2,3},{3,2,4,1}};
    for(int i=0;i<3;i++)
    {
        cout<<endl;
        for(int j=0;j<4;j++)
            cout<<T[i][j];
    }

    return 0;
}
