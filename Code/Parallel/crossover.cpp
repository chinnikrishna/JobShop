#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstring>
#include <ctime>
#include "crossover.h"
#define CROSSOVER_PART	(0.7)

using namespace std;

int CreateNewPopulation(Individual OldPop[],int population,Individual *NewPop,int NumJobs,int NumMachines)
{

    string parent1,parent2;
    int len_crossover = NumJobs * NumMachines * CROSSOVER_PART;
    //Calculating Total fitness
    int TotalFitness=0;
    int x=0,y=1;

    for(int i=0;i<population;i++)
    {

        x=rand()%((population));
        y=rand()%((population));
        while(x==y)
        {
           y=rand()%((population));
        }


        parent1=OldPop[x].Chromosome;
        parent2=OldPop[y].Chromosome;
        //cout<<"P1:"<<parent1<<endl;
        //cout<<"P2:"<<parent2<<endl;
        NewPop[i].Chromosome=CrossOver(parent1,parent2,len_crossover,NumJobs,NumMachines);
        //cout<<"Child:"<<NewPop[i].Chromosome<<endl;
    }

    return 0;
}
string RouletteSelection(int TotalFitness,Individual *Popu,int Population)
{
    float rand_num=((float)rand()/(RAND_MAX+1));
    float Slice = (float)(rand_num * TotalFitness);
    float FitnessSoFar = 0.0f;
    string tempchromsome;
    for (int i=0; i<Population; i++)
	{
		FitnessSoFar += Popu[i].Fitness;

		//if the fitness so far > random number return the chromo at this point
		if (FitnessSoFar >= Slice)
        {
            cout<<"I am here"<<endl;
            tempchromsome=Popu[i].Chromosome;
            cout<<Popu[i].Chromosome;
             cout<<tempchromsome;
            break;
        }
	}
    return tempchromsome;
}
string CrossOver(const string& parent,
				 const string& donor,
				 unsigned int len_crossover,
				 unsigned int numJobs,
				 unsigned int numMachines)
{
	string offspring;
	unsigned int len_chr = parent.length();

	gene* combinedChromosome = new gene[len_chr + len_crossover];

	/*
	 * STEP 1:
	 * Generate a combined chromosome containing part of donor
	 * genes included in the parent gene.
	 */

	GetCombinedChromosome(parent, donor, len_crossover, combinedChromosome,numMachines);

	/*
	 * STEP 2:
	 * Repair the combined chromosome by deleting genes from parent
	 * that match the name and index of implanted genes from donor
	 */

	offspring = RepairCombinedChromosome(combinedChromosome, len_chr + len_crossover, numJobs,
									len_crossover);


	if(combinedChromosome)
			delete[] combinedChromosome;
	return offspring;
}


void GetCombinedChromosome(const string& parent,
						   const string& donor,
						   unsigned int len_crossover,
						   gene* combined, unsigned int numMachines)
{
	string offspring;
	unsigned int len_chr = parent.length();
	unsigned int i;
	unsigned int l;

	// Randomly choose a crossover point in the donor
	//srand(time(NULL));
	unsigned int crossover_point = rand() % len_chr;

	unsigned int insertion_point = 0;
	char cutChrStartGene;

	// Store the positions (indexes) of the genes. Use this for marking deletions later.
	unsigned int* parentPos = new unsigned int [parent.length()];
	unsigned int* donorPos = new unsigned int [donor.length()];

	// Arrays to keep track of the position counts during the traversal
	unsigned int* genePosParent = new unsigned int [numMachines];
	unsigned int* genePosDonor = new unsigned int [numMachines];

	// Initialize arrays to zero
	memset(genePosParent,0,sizeof(unsigned int) * numMachines);
	memset(genePosDonor,0,sizeof(unsigned int) * numMachines);

	// Obtain indices for parent
	for (i = 0; i < parent.length(); i++)
	{
		genePosParent[parent[i] - 'A']++;
		parentPos[i] = genePosParent[parent[i] - 'A'];
	}

	// Obtain indices for donor
	for (i = 0; i < donor.length(); i++)
	{
		genePosDonor[donor[i] - 'A']++;
		donorPos[i] = genePosDonor[donor[i] - 'A'];
	}

#ifdef __debug__

	cout << endl << "Length of crossover string = " << len_crossover << endl;
	cout << endl << "Crossover point in donor (Starts with zero) = " << crossover_point << endl;

#endif

	// If crossover point makes implant genes wraps around the donor,
	// then no need to consider insertion point for parent. The donor genes
	// will simply wrap around the parent
	if(len_chr - crossover_point < len_crossover)
	{
		unsigned int first_donor_part_end_index = len_crossover - (len_chr - crossover_point + 1);

		// Copy first part of the donor
		// Cannot delete these genes
		for(i = 0; i <= first_donor_part_end_index; i++)
		{
			combined[i].name = donor[i];
			combined[i].canDelete = false;
			combined[i].pos = donorPos[i];
		}

		// Copy the whole parent
		for(i = 0; i < len_chr; i++)
		{
			combined[first_donor_part_end_index + i + 1].name = parent[i];
			combined[first_donor_part_end_index + i + 1].canDelete = true;
			combined[first_donor_part_end_index + i + 1].pos = parentPos[i];
		}

		// Now copy the end part of the donor
		l = 0;
		for(i = crossover_point; i < len_chr; i++)
		{
			combined[first_donor_part_end_index + len_chr + l + 1].name = donor[i];
			combined[first_donor_part_end_index + len_chr + l + 1].canDelete = false;
			combined[first_donor_part_end_index + len_chr + l + 1].pos = donorPos[i];
			l++;
		}

	}
	// Else if donor's crossover part does not wrap around donor,
	// then insert the implant genes at insertion point for parent
	else
	{
		// Compute the insertion point for parent
		cutChrStartGene = donor[crossover_point];
		insertion_point = GetInsertionPoint(parent, parentPos, cutChrStartGene, donorPos[crossover_point]);

#ifdef __debug__
		cout << "Insertion point in parent (Starts with zero) = " << insertion_point << endl;
#endif
		//Copy parent genes till the insertion point
		for(i = 0; i < insertion_point; i++)
		{
			combined[i].name = parent[i];
			combined[i].canDelete = true;
			combined[i].pos = parentPos[i];
		}

		// Copy the implant genes from donor
		// Cannot delete these genes
		l = 0;
		for(i = insertion_point; i < insertion_point + len_crossover; i++)
		{
			combined[i].name = donor[l + crossover_point];
			combined[i].canDelete = false;
			combined[i].pos = donorPos[l + crossover_point];
			l++;
		}

		// Copy the rest of the parent
		l = 0;
		for(i = insertion_point; i < len_chr; i++)
		{
			combined[insertion_point + len_crossover + l].name = parent[i];
			combined[insertion_point + len_crossover + l].canDelete = true;
			combined[insertion_point + len_crossover + l].pos = parentPos[i];
			l++;
		}
	}


#ifdef __debug__

		cout << endl << "Combined string format: <Gene> : <donor=0, parent=1> : <index>" << endl;
		cout << "Combined string is: ";

		// Print the combined chromosome
		for(i = 0; i < len_chr + len_crossover; i++)
		{
			cout << combined[i].name << ":" << combined[i].canDelete << ":" << combined[i].pos << "  ";
		}
		cout << endl;

		if(donorPos)
			delete[] donorPos;

		if(parentPos)
			delete[] parentPos;

		if(genePosParent)
			delete[] genePosParent;
		if(genePosDonor)
			delete[] genePosDonor;

#endif
}

unsigned int GetInsertionPoint(const string& parent, unsigned int* parentPos, unsigned char cutChrStartGene, unsigned int cutChrStartGenePos)
{
	unsigned int insertion_point = 0;

	unsigned int i = 0;
	for(i = 0; i < parent.length(); i++)
	{
		if((parent[i] == cutChrStartGene) && (parentPos[i] == cutChrStartGenePos))
		{
			insertion_point = i + 1;
			break;
		}
	}

	return insertion_point;
}

string RepairCombinedChromosome(gene* combinedChromosome, unsigned int len, unsigned int numJobs,
								unsigned int len_crossover)
{
	string repairedChromosome;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int l = 0;

	// Maintain gene count for each gene type (gene is a job)
	unsigned int* implantGeneCount = new unsigned int [numJobs];

	gene* implantGenes = new gene [len_crossover];

	// Separate out implanted genes in an array
	l = 0;
	for(i = 0; i < len; i++)
	{
		if(!combinedChromosome[i].canDelete)
		{
			implantGenes[l] = combinedChromosome[i];
			l++;
		}
	}

	// Now mark for deletion each parent gene which is in the implanted gene
	//std::cout << std::endl;

#ifdef __debug__
	cout << "Genes marked for deletion: <name:index> = ";
#endif

	for(i = 0; i < len_crossover; i++)
	{
		for(j = 0; j < len; j++)
		{
			if(combinedChromosome[j].canDelete && combinedChromosome[j].name == implantGenes[i].name && combinedChromosome[j].pos == implantGenes[i].pos)
			{
#ifdef __debug__
				cout << combinedChromosome[j].name << ":" << combinedChromosome[j].pos << " ";
#endif
				combinedChromosome[j].name = '-';

			}
		}
	}


#ifdef __debug__
	cout << endl;
#endif

#ifdef __debug__
	cout << "Removed Genes: " ;
#endif

	// Now remove the genes and produce the offspring
	for(i = 0; i < len; i++)
	{
#ifdef __debug__
		cout << combinedChromosome[i].name << " ";
#endif

		if(combinedChromosome[i].name != '-')
		{
			repairedChromosome += combinedChromosome[i].name;
		}
	}

#ifdef __debug__
	cout << endl;
#endif

	if(implantGeneCount)
		delete[] implantGeneCount;

	if (implantGenes)
		delete[] implantGenes;

	return repairedChromosome;
}

bool validateChromosome(const string& chr, unsigned int numJobs, unsigned int numMachines)
{
	// Easiest check. Remember: Number of tasks = number of machines
	if(chr.length() != numJobs * numMachines)
		return false;

	unsigned int i = 0;

	// Default. Optimistic.
	bool isValid = true;

	// Array to store counts of tasks for each job
	unsigned int * totalTasks = new unsigned int [numJobs];

	// Initialize to zero
	memset(&totalTasks[0],0,sizeof(unsigned int) * numJobs);

	for(i = 0; i < chr.length(); i++)
	{
		totalTasks[chr[i] - 'A']++;
	}

	for(i = 0; i < numJobs; i++)
	{
		if(totalTasks[i] != numMachines)
			isValid = false;
	}

	if(totalTasks)
		delete[] totalTasks;

	return isValid;
}
