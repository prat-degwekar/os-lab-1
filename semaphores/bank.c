#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
//#include <sleep.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define N 20			//no of customers
#define MAXMON 2000		//maximum transaction amount


sem_t mutex , count;
sem_t acc[ N ];

int accnt[N];
int bankbal = 0;

void* runner( void *params );

void* request( void *params );

/*void checkout( int n )
{
	sem_wait ( &mutex );

	printf( "Application %d is in mutex, checking for license availability...\n" , n );

	sem_wait( &app );

	printf( "Application %d has gotten the license!\n\n" , n );

	sem_post( &mutex );
}

void release( int n )
{

	sem_wait( &mutex );

	printf( "Application %d is ready to release the licence...\n" , n );

	sem_post( &app );

	printf( "Application %d has released the license!\n\n" , n );

	sem_post( &mutex );
}*/

void debit( int n , int t )
{

	//acquire counter lock

	sem_wait( &count );

	//debit money from account number n for token number t

	//pick a random +ve integer for adding to bank account

	int sval = 0;
	sem_getvalue( &count , &sval );

	printf( "At counter number %d , for token number %d\n\n" , sval , t );

	//srand( time ( NULL ) * rand() % 20 );

	int mon = 0;

	srandom( t );

	mon = random() % MAXMON ;

	printf( "Credited an amount of $%d to account number %d, as per request from customer with token number %d\n" , mon , (n+1) , t );


	bankbal+= mon;

	accnt[n]+= mon;

	printf( "Account balance = %d , global balance = %d\n\n" , accnt[ n ] , bankbal );

	//release counter lock

	sem_post( &count );

}

void credit( int n , int t )
{

	//acquire counter lock

	sem_wait( &count );
	
	//acquire mutex lock - to check total bank balance does not exceed -> 1 credit at a time

	sem_wait( &mutex );

	//acquire account lock

	sem_wait( &acc[ n ] );

	//generate random +ve number for credit amount

	//srand( time( NULL ) * rand() % 10 );

	srandom( t );

	int mon = 0;

	mon = random() % MAXMON;

	//check bankbal and accnt balance

	if( bankbal < mon || accnt[ n ] < mon )
	{
		printf( "This transaction cannot proceed, not enough funds!\n\n");

		sem_post( &acc[n] );

		sem_post( &mutex );

		sem_post( &count );
		
		return;
	}

	bankbal-= mon;
	accnt[ n ] -= mon;

	int sval = 0;
	sem_getvalue( &count , &sval );

	printf( "At counter number %d , for token number %d\n\n" , sval , t );

	//release account lock

	sem_post( &acc[ n ] );

	//release mutex

	sem_post( &mutex );

	//release counter lock

	printf( "Debited an amount of $%d from account number %d , as per request from customer with token number %d\n\n" , mon , (n+1) , t );
	printf( "Account balance = %d , global balance = %d\n\n" , accnt[ n ] , bankbal );

	sem_post( &count );

}

void* request( void *params )
{
	int *num = (int *)(params);
	int val = *num;

	printf( "inside for request number : %d\n\n" , val );

	while(1)
	{
		/*checkout( val );
		sleep( 0 );
		release( val );
		sleep(1);*/

		//pick a random 0 - N accnt number

		//srand( time( NULL ) * rand() % 5 );

		int n = 0;

		srandom( val );

		n = random() % N ;

		//pick debit or credit

		int pick = 0;

		pick = random() % 2;

		//call debit( accnt number , val - which is token num.) if debit no mutex required

		//call credit( accnt number , val ) if credit -> requires mutex on accnt - i.e the acc mutex

		if( pick == 0 )
			debit( n , val );
		else credit( n , val );

		sleep(1);

	}
}

int main()
{
	int i , n = 3;	//n is no. of counters

	/*printf("enter number of licences : ");
	scanf( "%d\n" , &n );*/


	for( i = 0 ; i<N ; i++ )
		accnt[i] = 0;

	pthread_t pth[ N ];

	sem_init( &mutex , 0 , 1 );
	sem_init( &count , 0 , n );

	for( i=0 ; i<N ; i++ )
		sem_init( &acc[i] , 0 , 1 );

	for( i = 0 ; i < N * 5 ; i++ )
    {
    	//printf("here");
        pthread_create( &pth[i] , NULL , request , /*&tnum[i]*/ &i );
        printf("Customer %d is requesting account access\n" , i+1);
    }
    for( i = 0 ; i < N ; i++ )
        pthread_join( pth[i],NULL);

    return 0;

}