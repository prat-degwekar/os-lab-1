#include <pthread.h>
#include <stdio.h>

/*int arr[3][3] = {{0}};
int o1[3][3] = {{0}};
int o2[3][3] = {{0}};

struct mat
{

   int r;
   int c;

};

/* this function is run by the second thread */
/*void* inc_x(void* x_void_ptr)
{

   /* increment x to 100 */
   /*int *x_ptr = (int *)x_void_ptr;
   while(++(*x_ptr) < 100);

   printf("x increment finished\n");

   /* the function must return something - NULL will do */
   
   /*return NULL;

}*/

int arr[10] = { 8 , 5 , 15 , 12 , 11 , 13 , 17 , 7 , 9 , 1 };

/*void* matm( void* matptr )
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

}*/

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition ( int low, int high )
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void* quickSort( void* nums )
{

   int *num = (int *)nums;

   int low = num[0];
   int high = num[1];

    if (low <= high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition( low, high );
 
        // Separately sort elements before
        // partition and after partition

         pthread_t t1;

         pthread_t t2;

         pthread_attr_t attr;

   
         pthread_attr_init( &attr );

        //pid_t pid = vfork();

        /*if(pid < 0)
        {
            cout<<"erroneous vfork\n\n";
            exit(0);
        }*/

        /*if(pid == 0)
        {
            quickSort(arr, low, pi - 1);
            exit(0);
        }*/

        /*else
        {
            quickSort(arr, pi + 1, high);
        }*/

         int numb[2] = {0};

         numb[0] = low;
         numb[1] = pi - 1;

         if( pthread_create( &t1 , &attr , quickSort , numb ) )
         {
            printf("error in creating thread numbered : i = 1\n\n");

            pthread_exit(0);

         }

         if( pthread_join( t1 , NULL) )
         {
            printf("error joining threads\n\n");
            pthread_exit(0);

         }

         numb[0] = pi + 1;
         numb[1] = high;

         if( pthread_create( &t2 , &attr , quickSort , numb ) )
         {
            printf("error in creating thread numbered : i = 1\n\n");

            pthread_exit(0);

         }

         if( pthread_join( t2 , NULL) )
         {
            printf("error joining threads\n\n");
            pthread_exit(0);

         }

    }
}
 
/* Function to print an array */
void printArray( int size )
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
}


int main()
{

   /* this variable is our reference to the second thread */
   /*pthread_t inc_x_thread;

   pthread_t mat_thread[9];

   pthread_attr_t attr;

   
   pthread_attr_init( &attr );*/


   /* create a second thread which executes inc_x(&x) */
   /*if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) 
   {

      fprintf(stderr, "Error creating thread\n");
 
      return 1;

    
   }*/

   /*for(i = 0 ; i<9 ; i++)
   {
      if( pthread_create( &mat_thread[i] , &attr , matm , &mm[i/3][i%3] ) )
      {
	 printf("error in creating thread numbered : i = %d\n\n",i);

	 return 1;

      }

   }*/
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
   /*printf("x: %d, y: %d\n\n\n", x, y);

   if( pthread_join( mat_thread[0] , NULL) )
   {
      printf("error joining threads\n\n");
      return 1;

   }*/

   //print matrices

   /*for(i=0 ; i<3 ; i++)
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
   }*/

   int numb[2] = {0};

   numb[0] = 0;
   numb[1] = 9;

   quickSort(numb);

   printf("\n");

   printArray(10);

   printf("\n\n\n");

   return 0;

}
