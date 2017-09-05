#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
	int pid = fork();

	if(pid == 0)
	{
		sleep(5);
		cout<<"\nchild ded\n";
	}
	else
	{
		cout<<"parent ded";
	}

	return 0;
}