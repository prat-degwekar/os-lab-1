#include "proceed.h"

void fcfs( process p[] , int n)
{
	for(int i=0 ; i<n ; i++)
	{
		for(int j=0 ; j<(n-i-1) ; j++)
		{
			if( p[j].getat() > p[j+1].getat() )
			{
				process temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}

	//set in order and add completion time

	int c=0;

	for(int i=0 ; i<n ; i++)
	{
		c+=p[i].getbt();
		p[i].setct(c);
		p[i].calwt();
		p[i].caltat();
	}

	//end

	int totwt = 0;

	for(int i=0 ; i<n ; i++)
	{
		totwt+=p[i].getwt();
	}

	float avgwt = (float)(totwt) / (float)(n);

	cout<<"average waiting time : "<<avgwt"\n\n";

}