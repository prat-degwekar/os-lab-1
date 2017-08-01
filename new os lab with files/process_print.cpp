#include "proceed.h"
#include <iostream>

using namespace std;

void print_process( process p[] , int n )
{
	for(int i=0 ; i<n ; i++)
	{
		cout<<"pid : "<<p[i].getpid()<<"\nat : "<<p[i].getat()<<"\tbt : "<<p[i].getbt()<<"\twt : "<<p[i].getwt()<<"\tct : "<<p[i].getct()<<"\ttat : "<<p[i].gettat()<<"\n\n";
		cout<<"----------------------------------\n\n";
	}
}