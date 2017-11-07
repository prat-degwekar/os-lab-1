#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
//#include <sleep.h>
#include <unistd.h>
#include <stdlib.h>

#define N 20


sem_t mutex , app;

void* runner( void *params );

void* request( void *params );

void checkout( int n )
{
	sem_wait ( &mutex );

	printf( "Application %d is in mutex, checking for license availability...\n" , n );

	sem_wait( &app );

	printf( "Application %d has gotten the license!\n\n" , n );

	sem_post( &mutex );
}

void release( int n )
{

	//sem_wait( &mutex );

	printf( "Application %d is ready to release the licence...\n" , n );

	sem_post( &app );

	printf( "Application %d has released the license!\n\n" , n );

	//sem_post( &mutex );
}

void* request( void *params )
{
	int *num = (int *)(params);
	int val = *num;

	printf( "inside for request number : %d\n\n" , val );

	while(1)
	{
		checkout( val );
		sleep( 0 );
		//system("ls");
		int k = random()%20000;
		//system( "cowthink " + k );
		system("fortune");
		release( val );
		sleep(1);
	}
}

int main()
{
	int i , n;

	printf("enter number of licences : ");
	scanf( "%d" , &n );

	int tnum[N];

	for( i = 0 ; i<N ; i++ )
		tnum[i] = i;

	pthread_t pth[20];

	sem_init( &mutex , 0 , 1 );
	sem_init( &app , 0 , n );

	for( i = 0 ; i < N ; i++ )
    {
    	//printf("here");
        pthread_create( &pth[i] , NULL , request , &tnum[i] );
        printf("Application %d is requesting\n",i+1);
    }
    for( i = 0 ; i < N ; i++ )
        pthread_join( pth[i],NULL);

    return 0;

}