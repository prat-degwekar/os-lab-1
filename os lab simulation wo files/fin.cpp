#include "proceed.h"
#include <iostream>

using namespace std;

int main()
{
	process p5(4 , 2 , 3 , "001");	//at , bt , pr , pid
	process p3( 2 , 5 , 6 , "002");
	process p1(0 , 3 , 1 , "003");
	process p2(1 , 4 , 4 , "004");
	process p4(3 , 1 , 2 , "005");

	cout<< ((0<=0)) ? "0" : "1";


	process* p = new process[5];
	p[0] = p1;
	p[1] = p2;
	p[2] = p3;
	p[3] = p4;
	p[4] = p5;

	cout<<"first completion time = "<<p[0].getct()<<"\n\n\n";

	prp( p , 5 );
	print_process( p , 5 );

	return 0;
}