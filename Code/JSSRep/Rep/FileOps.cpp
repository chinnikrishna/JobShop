#include "Operations.h"
int ReadBenchMark(string Filename,int *Machines,int *Jobs)
{
    char M[50];
    char J[50];
    int i;
    //Input stream for the file
    ifstream inFile;
    //Opening the file
    inFile.open(Filename.c_str());
    //Error Handler
    if(!inFile)
    {
        cout<<"Can't find the benchmark file named "<<Filename<<endl;
        exit(1);
    }
    //Getting number of machines and jobs
    for(i=0;i<1;i++){
        inFile>> J >> M;
    }
    *Machines=atoi(M);
    *Jobs=atoi(J);
    inFile.close();
    return 0;
}
