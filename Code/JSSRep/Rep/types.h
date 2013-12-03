#ifndef __TYPES_H__
#define __TYPES_H__

#include <string>
using namespace std;
//Data Structure for Individual
struct Individual
{
    string Chromosome;
    float Fitness;
};

typedef struct _gene
{
	char name;
	unsigned int pos;
	bool canDelete;
}gene;

#endif // __TYPES_H__
