#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{
	int inp = 0;
	int pid = vfork();
	if(pid < 0)
	{
		cout<<"erroneous gg\n\n";
		return -1;
	}

	if(pid == 0)
	{
		/*for(int i=0 ; i<=10 ; i+=2)
			cout<<i<<" , ";*/
		cout<<"input : ";
		cin>>inp;
		cout<<" <- thats child!\n\n";
	}

	else
	{
		wait(0);
		/*for(int i=2 ; i <= (inp/2) ; i++)
			if( inp % i == 0 )
			{
				cout<<"noon prime\n\n";
				return 1;
			}
		cout<<"prime number!\n\n";*/
		bool arr[inp+1] = {0};
		for( int i=2 ; i <= sqrt(inp) ; i++ )
		{
			if(arr[i] == 1)
				continue;
			for(int j = 1 ; i*j <= inp ; j++ )
			{
				arr[i*j] = 1;
			}
		}

		for(int i=2 ; i<=inp ; i++ )
		{
			if(arr[i] == 0)
			{
				cout<<i<<" , ";
			}
		}
		cout<<endl;
		cout<<" and thats parent!\n\n";
	}

	exit(0);
	return pid;
}