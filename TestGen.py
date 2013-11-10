#Script to generate test cases randomly

#Imports
from random import randrange;
from random import sample;
#Getting inputs from user
NoCases=input("Enter number of cases needed:");
NumMac=input("Enter number of machines in Job Shop:");
MaxTime=input("Enter the max time each job can take:");
#Creating a data file for writing
File=open("Test.txt","w");
for NC in range(1,int(NoCases)+1):
	File.write("\n"+str(NC)+",\t");
	K=randrange(2,int(NumMac)+1);
	Pop=range(1,int(NumMac)+1);
	Seq=sample(Pop,K);
	File.write(str(Seq));
	File.write("\t[");
	for Time in range (1,K+1):
		File.write(str(randrange(1,int(MaxTime)+1))+",");
	File.write("]");
File.close();
    

