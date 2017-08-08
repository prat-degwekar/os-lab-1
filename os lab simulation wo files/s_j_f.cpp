#include "proceed.h"
#include <iostream>

using namespace std;

void sjf( process p[] , int n )
{
	int curt = 0; 
	for(int i=0 ; i<n ; i++)
	{
		//assumed first process comes in at 0

		int minbt = 9;
		int ind = 0;

		for(int j=0 ; j<n ; j++)
		{
			/*if( p[j].getat() > curt || p[j].getct() >= 0 )
				continue;*/

			if( p[j].getat() <= curt && p[j].getct() < 0 )
			{	
				//cout<<"in \n";

				if(p[j].getbt() == minbt )
				{
					if(p[j].getat() < p[ind].getat())
					{
						ind = j;
					}
				}

				else if(p[j].getbt() < minbt )
				{
					minbt = p[j].getbt();
					ind = j;
					//cout<<"came here once";
				}

			}
			//cout<<"in here?"<<endl;

			/*if(p[j].getbt() < minbt )
			{
				minbt = p[j].getbt();
				ind = j;
				cout<<"came here once";
			}*/
		}

		curt+=p[ind].getbt();
		p[ind].setct(curt);
		p[ind].calwt();
		p[ind].caltat();

	}

	int totwt = 0;

	for(int i=0 ; i<n ; i++)
	{
		totwt+=p[i].getwt();
	}

	float avgwt = (float)(totwt) / (float)(n);

	cout<<"average waiting time : "<<avgwt"\n\n";

}