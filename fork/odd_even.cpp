#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
	int pid = fork();
	if(pid < 0)
	{
		cout<<"erroneous gg\n\n";
		return -1;
	}

	if(pid == 0)
	{
		for(int i=0 ; i<=10 ; i+=2)
			cout<<i<<" , ";
		cout<<" <- thats child!\n\n";
	}

	else
	{
		wait(0);
		for(int i=1 ; i<10 ; i+=2)
			cout<<i<<" , ";
		cout<<" and thats parent!\n\n";
	}

	return pid;
}