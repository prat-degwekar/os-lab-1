#include <iostream>
#include "proceed.h"

void srt( process p[] , int n )
{
	int curt = 0;
	int curind = 0;

	int sum_bt = 0;

	for(int i=0 ; i<n ; i++)
		sum_bt+=p[i].getbt();

	//get min at

	int minat = 999;
	int miniind = 0;

	for(int i=0 ; i<n ; i++)
	{
		if(p[i].getat()<minat)
		{
			minat = p[i].getat();
			miniind = i;
		}
	}

	curind = miniind;

	cout<<"time"<<"\t"<<"prevind"<<"\t"<<"curind"<<"\t"<<"bt left"<<"\t"<<"pid"<<endl;

	int flg = 0;

	for(int i=0 ; i < sum_bt ; i++)
	{
		int minbt = 9999;
		int ind = 0;
		int prevind = curind;

		for(int j=0 ; j<n ; j++)
		{

			if( p[j].getat() <= curt && p[j].getct() < 0 )
			{
				if( p[j].getbt() < minbt )
				{
					minbt = p[j].getbt();
					ind = j;
				}
			}
		}

		if(flg == 1)
		{
			flg = 0;
			i--;
			continue;
		}

		if( ind == curind )
		{
			p[ind].setbt( minbt - 1 );
			if(p[ind].getbt() == 0)
			{
				//process done
				
				p[ind].setct(curt + 1);
				p[ind].caltat();
				p[ind].calwt();
				
				//set next process to load
				
				for(int k=0 ; k<n ; k++)			//may not need to do this
				{
					if(p[k].getct() >= 0)
						continue;
					curind = k;
					break;
				}

				flg = 1;

				/*if( p[j].getat() <= curt && p[j].getct() < 0 )
				{
					if( p[j].getbt() < minbt )
					{
						minbt = p[j].getbt();
						ind = j;
					}
				}*/

			}
		}

		else
		{
			int kk = p[curind].getbt();
			
			p[curind].setbt(kk - 1);
			
			if( p[curind].getbt() == 0 )
			{
				p[curind].setct( curt + 1);
				p[curind].caltat();
				p[curind].calwt();
				
				//set next process to load

				/*for(int k=0 ; k<n ; k++)
				{
					if(p[k].getct() >= 0)
						continue;
					curind = k;
					break;
				}*/

			}

			curind = ind;
		}

		cout<<curt<<"\t"<<prevind<<"\t"<<curind<<"\t"<<p[curind].getbt()<<"\t"<<p[curind].getpid()<<endl;

		curt++;

	}
}