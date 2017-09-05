#include <iostream>
#include "proceed.h"
#include <queue>

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
	queue<int> qu;
	int vis[n];

	//q.enqueue(0);

	for(int i=0 ; i<n ; i++)
		vis[i] = 0;

	cout<<"i\tcurslic\tnextsli\tj\tpid\tbt\n";

	int flag = 0;

	for(int i=0 ; flg2 == 0 ; )
	{

		//add new elements to queue

		for(j=0 ; j<n ; j++)
		{
			if( p[j].getat() <= curt && p[j].getct() < 0 )
			{
				//check if j already exists

				for(int ij = 0 ; ij < q.size() ; ij++)
				{
					qu.push(q.front());
					int temp = q.front();
					q.pop();
					q.push(temp);
				}

				for(int ij=0 ; ij<qu.size() ; ij++)
				{
					int temp = qu.front();
					if(temp == j)
					{
						flag = 1;
						break;
					}
					else
					{
						qu.pop();
						qu.push(temp);
					}
				}

				if(flag == 1)
				{
					flag = 0;
					continue;
				}

				q.push(j);
				//flg = 1;
			}
		}

		/*if(flg == 0)
		{
			//j = (j + 1) % n;
			continue;
		}*/
		
		//enqueueing part is done , now to execute
	
		//dequeue , run a slice , check if bt < 0 -> enqueue again. finally one dequeue and enqueue w/o run process.

		for(int ij = 0 ; ij<q.size() ; ij++)
		{
			int temp = q.front();

			/*if(vis[temp] == 1)
				break;
			else
				vis[temp] = 1;*/
			
			if(p[temp].getbt() < cur_slice )
				next_slice+= cur_slice - p[temp].getbt();

			p[temp].setbt(p[temp].getbt() - cur_slice);

			if(p[temp].getbt() <= 0)
			{
				p[temp].setct( curt + p[temp].getbt() + cur_slice );
				p[temp].setbt(0);
				p[temp].caltat();
				p[temp].calwt();
				q.pop();
				flg = 1;
				cout<<"process : "<<p[temp].getpid()<<" just completed!"<<endl;

			}

			else
			{
				q.pop();
				q.push(temp);
			}

			cout<<i<<"\t"<<cur_slice<<"\t"<<next_slice<<"\t"<<temp<<"\t"<<p[temp].getct()<<"\t"<<p[temp].getbt()<<"\t"<<endl;

			/*cout<<"the queue : ";

			for(int ij = 0 ; ij < q.size() ; ij++)
				{
					int temp = q.front();
					cout<<temp<<" , ";
					q.pop();
					q.push(temp);
				}


			int rtr = 0;
			cin>>rtr;*/
			if(flg == 0)
			{
				i+=cur_slice;
				curt+=cur_slice;
				cur_slice = next_slice;
				next_slice = 3;
				//flg = 0;
			}
			else
			{
				i += cur_slice + 3 - next_slice;
				curt+=cur_slice + 3 - next_slice;
				cur_slice = next_slice;
				next_slice = 3;
			}
		}
		if(flg == 0)
		{
			int temp = q.front();
			q.pop();
			q.push(temp);
		}

		else
			flg = 0;

		//reset vis array

		for(int ij = 0 ; ij<n ; ij++)
			vis[ij] = 0;

		//cout<<i<<"\t"<<cur_slice<<"\t"<<next_slice<<"\t"<<j<<"\t"<<p[j].getpid()<<"\t"<<p[j].getbt()<<"\t"<<endl;
		

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

	}
}
