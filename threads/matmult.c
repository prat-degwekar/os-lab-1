#include <pthread.h>
#include <stdio.h>

int arr[3][3] = {{0}};
int o1[3][3] = {{0}};
int o2[3][3] = {{0}};

struct mat
{

   int r;
   int c;

};

/* this function is run by the second thread */
void* inc_x(void* x_void_ptr)
{

   /* increment x to 100 */
   int *x_ptr = (int *)x_void_ptr;
   while(++(*x_ptr) < 100);

   printf("x increment finished\n");

   /* the function must return something - NULL will do */
   
   return NULL;

}

void* matm( void* matptr )
{
   struct mat* m = ( struct mat*) matptr;
   int r = m->r;
   int c = m->c;

   //do matrix multiplication here
   
   int i=0 , j=0;

   for(i = 0 ; i < 3 ; i++ )
   {
      arr[r][c] += o1[r][i] * o2[i][c];
   }
  
   printf("finished for r = %d , c = %d \n\n",r,c);

   pthread_exit(0);

}

int main()
{

   int x = 0, y = 0,i = 0,j = 0;

   struct mat mm[3][3];
   
   for( i=0 ; i<3 ; i++)
      for(j=0 ; j<3 ; j++)
	 o1[i][j] = o2[i][j] = i+j;

   for( i=0 ; i<3 ; i++)
   {
      for(j=0 ; j<3 ; j++)
      {
	 mm[i][j].r = i;
	 mm[i][j].c = j;
      }
   }

   /* show the initial values of x and y */
   printf("x: %d, y: %d\n", x, y);

   /* this variable is our reference to the second thread */
   pthread_t inc_x_thread;

   pthread_t mat_thread[9];

   pthread_attr_t attr;

   
   pthread_attr_init( &attr );


   /* create a second thread which executes inc_x(&x) */
   /*if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) 
   {

      fprintf(stderr, "Error creating thread\n");
 
      return 1;

    
   }*/

   for(i = 0 ; i<9 ; i++)
   {
      if( pthread_create( &mat_thread[i] , &attr , matm , &mm[i/3][i%3] ) )
      {
	 printf("error in creating thread numbered : i = %d\n\n",i);

	 return 1;

      }

   }
   /* increment y to 100 in the first thread */
   /*while(++y < 100);

   printf("y increment finished\n");

   /* wait for the second thread to finish */
   
   /*if(pthread_join(inc_x_thread, NULL)) 
   {

	fprintf(stderr, "Error joining thread\n");
	return 2;

   }*/

   /* show the results - x is now 100 thanks to the second thread */
   printf("x: %d, y: %d\n\n\n", x, y);

   if( pthread_join( mat_thread[0] , NULL) )
   {
      printf("error joining threads\n\n");
      return 1;

   }

   //print matrices

   for(i=0 ; i<3 ; i++)
   {
      for(j=0 ; j<3 ; j++)
      {
         printf(" %d ",o2[i][j]);
      }
      
      printf("\n");
   }
   
   printf("\nthat was o2\n\n");

   for(i=0 ; i<3 ; i++)
   {
      for(j=0 ; j<3 ; j++)
	 printf(" %d " , arr[i][j]);

      printf("\n");
   }

   printf("\n\n\n");

   return 0;

}
