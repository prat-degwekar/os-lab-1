#include <pthread.h>
#include <stdio.h>

using namespace std;

int magicGen(int **arr , int n)
{
 
    // Initialize position for 1
    int i = n/2;
    int j = n-1;
 
    // One by one put all values in magic square
    for (int num=1; num <= n*n; )
    {
        if (i==-1 && j==n) //3rd condition
        {
            j = n-2;
            i = 0;
        }
        else
        {
            //1st condition helper if next number 
            // goes to out of square's right side
            if (j == n)
                j = 0;
            //1st condition helper if next number 
            // is goes to out of square's upper side
            if (i < 0)
                i=n-1;
        }
        if (arr[i][j]) //2nd condition
        {
            j -= 2;
            i++;
            continue;
        }
        else
            arr[i][j] = num++; //set number
 
        j++; i--; //1st condition
    }

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            cout<<arr[i][j]<<" ";
        cout<<endl;
    }

    return 1;
}

struct mat
{
    int n;          //number row/column
    int c;          //row or column separator
}

int magic_check(int **arr , int n)
{
 
    // Print magic square
    /*printf("The Magic Square for n=%d:\nSum of each row or column %d:\n\n",
            n, n*(n*n+1)/2);
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%3d ", arr[i][j]);
        printf("\n");
    }*/
    int reqval = n * ( (n * n ) + 1) / 2;

    //row check

    for(int i=0 ; i<n ; i++)
    {
    	int rowsum = 0;

    	for(int j=0 ; j<n ; j++)
    		rowsum += arr[i][j];

    	if(rowsum != reqval )
    	{
    		cout<<"error, row "<<i<<" does not match , not a magic square!"<<endl<<endl;
    		return -1;
    	}
    	else
    		cout<<"row "<<i<<" check\n";
    }

    //row check

    cout<<"\n\nnow column check\n\n";

    //column check

    for(int i=0 ; i<n ; i++)
    {
    	int colsum = 0;

    	for(int j=0 ; j<n ; j++)
    	{
    		colsum += arr[j][i];
    	}

    	if(colsum != reqval)
    	{
    		cout<<"error , column "<<i<<" does not match , not a magic square!"<<endl<<endl;
    		return -1;
    	}

    	else
    	{
    		cout<<"column "<<i<<" check\n";
    	}

    }

    //column check

    return 1;

}

int main()
{

	int n=0;
	cout<<"enter n : ";
	cin>>n;
	int **arr = new int* [n];
	for(int i=0 ; i<n ; i++)
		arr[i] = new int[n];
	for(int i=0 ; i<n ; i++)
		for(int j=0 ; j<n ; j++)
			arr[i][j] = 0;

	int pid = vfork();

	if(pid < 0)
	{
		cout<<"erroneous vfork\n\n";
		exit(0);
	}

	else if(pid == 0)
	{
		int k = magicGen(arr , n);
		exit(0);
	}
	else
	{

		wait(0);
		int k = magic_check(arr , n);
		if(k == -1)
		{
			cout<<"error!\n\n";
			return -1;
		}
		else
		{

			cout<<"success!\n\n";
			return 0;

		}

	}

	return 0;

}