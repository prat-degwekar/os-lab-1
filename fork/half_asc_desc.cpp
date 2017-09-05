#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <algorithm>

using namespace std;

int main()
{
	cout<<"enter 10 random elements ( um, i mean integers ) : ";
	int arr[10] = {0};
	for(int i=0 ; i<10 ; i++)
		cin>>arr[i];

	int pid = fork();
	if(pid < 0)
	{
		cout<<"erroneous gg\n\n";
		return -1;
	}

	if(pid == 0)
	{
		sort(arr , arr + 5);
		for(int i=0 ; i<5 ; i++)
			cout<<arr[i]<<" , ";
		cout<<" <- thats child!\n\n";
	}

	else
	{
		wait(0);
		sort(arr + 5 , arr+10 , greater<int>() );
		for(int i=5 ; i<10 ; i++)
			cout<<arr[i]<<" , ";
		cout<<" and thats parent!\n\n";
	}

	return pid;
}