#include <iostream>
#include "proceed.h"
#include <queue.h>

void rr( process p[] , int n )
{
	int curt = 0;
	int curind = 0;
	int sum_bt = 0;

	for(int i=0 ; i<n ; i++)
		sum_bt+=p[i].getbt();

	int next_slice = 3;
	int cur_slice = 3;
	int j = 0;
	int flg = 0;
	int flg2 = 0;
	queue<int> q;
	int vis[n];

	//q.enqueue(0);

	for(int i=0 ; i<n ; i++)
		vis[i] = 0;

	cout<<"i\tcurslic\tnextsli\tj\tpid\tbt\n";

	for(int i=0 ; flg2 == 0 ; )
	{
		for(j=0 ; j<n ; j++)
		{
			if( p[j].getat() <= curt && p[j].getct() < 0 )
			{
				/*if(p[j].getbt() < cur_slice)
				{
					next_slice+=cur_slice - p[j].getbt();
				}*/
	
				//p[j].setbt( p[j].getbt() - cur_slice );
	
				/*if(p[j].getbt() <= 0)
				{
					p[j].setct( curt + next_slice - 3 + cur_slice );
					p[j].caltat();
					p[j].calwt();
					p[j].setbt(0);
				}*/
				q.enqueue(j);
				flg = 1;
			}
		}

		/*if(flg == 0)
		{
			//j = (j + 1) % n;
			continue;
		}*/
		
		//enqueueing part is done , now to execute
	
		//dequeue , run a slice , check if bt < 0 -> enqueue again. finally one dequeue and enqueue w/o run process.
		i+=cur_slice;
		curt+=cur_slice;
		cur_slice = next_slice;
		next_slice = 3;
		flg = 0;

		/*cout<<i<<"\t"<<cur_slice<<"\t"<<next_slice<<"\t"<<j<<"\t"<<p[j].getpid()<<"\t"<<p[j].getbt()<<"\t"<<endl;
		j = ( j + 1 ) % n;

		for(int jj = 0 ; jj < n ; jj++)
		{
			if( p[jj].getbt() > 0 )
			{
				flg2 = 1;
				break;
			}
		}

		if(flg2 == 1)
			flg2 = 0;
		else
			break;

		*/
	}
}
