#include "proceed.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <sys/stat.h>
#include <string.h>

using namespace std;

int main()
{
	/*process p1(4 , 2 , "001");
	process p2( 2 , 5 , "002");
	process p3(0 , 3 , "003");
	process p4(1 , 4 , "004");
	process p5(3 , 1 , "005");*/

	string str = "some file ";

	struct tm * timeinfo1;
	struct tm * timeinfo2;
	struct tm * timeinfo3;
	struct tm * timeinfo4;
	struct tm * timeinfo5;

	int *bt = new int[5];
	time_t *tat = new time_t[5];

	cout<<"outside";

	for(int i=0 ; i<5 ; i++)
	{
		ifstream ifile;

		string k = to_string(i+1);
		
		string temp = str + k;
		cout<<"temp = "<<temp<<endl;

		ifile.open(temp.c_str());

		string word;

		int count = 0;
		int at = 0;
		//int bt = 0;

		cout<<"was here...";

		while(!ifile.eof())
		{
			ifile >> word;
			count++;
		}

		cout<<"burst time number "<<i<<" : "<<count<<endl<<endl;

		bt[i] = count;

		struct stat t_stat;
    	stat(temp.c_str(), &t_stat);
    	struct tm * timeinfo = localtime(&t_stat.st_ctime);
    	printf("File time and date: %s", asctime(timeinfo));

    	tat[i] = mktime(timeinfo);
    	
    	/*switch(i)
    	{
    		case 0 : timeinfo1 = timeinfo;
    				 break;

    		case 1 : timeinfo2 = timeinfo;
    				 break;

    		case 2 : timeinfo3 = timeinfo;
    				 break;

    		case 3 : timeinfo4 = timeinfo;
    				 break;

    		case 4 : timeinfo5 = timeinfo;
    				 break;
    	}*/


		ifile.close();
	}

	process* p = new process[5];

	//find min at

	int minat = 99999;
	int minind = 0;

	for(int i=0 ; i<5 ; i++)
	{
		if((int)tat[i] < minat)
		{
			minat = tat[i];
			minind = i;
		}
	}

	cout<<"min = "<<minat<<" , at : "<<minind<<endl;

	//get this right

	for(int i=0 ; i<5 ; i++)
	{
		p[i].load( int ( difftime(tat[i] , tat[minind]) ) , bt[i] , "00"+to_string(i) );
	}

	long int kk = difftime(tat[2] , tat[0]);
	cout<<"int time : "<<kk<<endl;

	cout<<"first arrival time = "<<p[0].getat()<<"\n\n\n";

	sjf( p , 5 );
	print_process( p , 5 );

	return 0;
}