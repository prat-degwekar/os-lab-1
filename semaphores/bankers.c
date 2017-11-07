#include <stdio.h>

// Number of processes

const int P = 5;

// Number of resources

const int R = 3;

void calculateNeed( int need[P][R] , int maxm[P][R] , int allot[P][R] )
{
	int i , j;

	for ( i = 0 ; i < P ; i++ )
	{
		for ( j = 0 ; j < R ; j++ )
		{	
			// Need of instance = maxm instance - allocated instance

			need[i][j] = maxm[i][j] - allot[i][j];

		}
	}
}

// Function to find the system is in safe state or not

int isSafe( int processes[] , int avail[] , int maxm[][R] , int allot[][R] )
{
	int need[P][R];

	int i , p , k ;

	calculateNeed(need, maxm, allot);

	// Mark all processes as not finished

	int finish[5] = { 0 };

	for( i=0 ; i<P ; i++ )
		finish[i] = 0;

	// To store safe sequence

	int safeSeq[P];

	// Make a copy of available resources

	int work[R];

	for ( i = 0; i < R ; i++ )
		work[i] = avail[i];

	// While all processes are not finished or system is not in safe state.

	int count = 0;

	while (count < P)
	{
		// find a process

		int found = 0;

		for ( p = 0 ; p < P ; p++ )
		{
			// Check if process finished

			if (finish[p] == 0)
			{
				// Check if for all resources of process, need is less than work

				int j;

				for ( j = 0 ; j < R ; j++ )
				{
					
					if (need[p][j] > work[j])
						break;

				}

				if ( j == R )
				{
					// Add the allocated resources of current P to work resources i.e.free the resources

					for ( k = 0 ; k < R ; k++ )
						work[k] += allot[p][k];

					// Add this process to safe sequence.

					safeSeq[count++] = p;

					// Mark this p as finished

					finish[p] = 1;

					found = 1;
				}
			}
		}

		// If we could not find a next process in safe sequence.

		if (found == 0)
		{

			printf( "System is not in safe state" );
			return 0;

		}

	}

	// print safe sequence

	printf(" System is in safe state.\nSafe sequence is: " );

	for ( i = 0; i < P ; i++ )
	{
		printf(" %d " , safeSeq[i] );
	}

	return 1;
}

// Driver code

int main()
{
	int processes[] = {0, 1, 2, 3, 4};

	// Available instances of resources

	int avail[3] = {3, 3, 2};

	// Maximum R that can be allocated to processes

	int maxm[5][3] = { {7, 5, 3} , {3, 2, 2} , {9, 0, 2} , {2, 2, 2} , {4, 3, 3} };

	// Resources allocated to processes

	int allot[5][3] = { {0, 1, 0} ,	{2, 0, 0} , {3, 0, 2} ,	{2, 1, 1} ,	{0, 0, 2} };

	// Final
					
	isSafe(processes, avail, maxm, allot);

	return 0;
}