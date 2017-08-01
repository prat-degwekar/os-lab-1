#include "proceed.h"
#include <iostream>

using namespace std;

int main()
{
	process p1(4 , 2 , "001");
	process p2( 2 , 5 , "002");
	process p3(0 , 3 , "003");
	process p4(1 , 4 , "004");
	process p5(3 , 1 , "005");

	cout<< ((0<=0)) ? "0" : "1";


	process* p = new process[5];
	p[0] = p1;
	p[1] = p2;
	p[2] = p3;
	p[3] = p4;
	p[4] = p5;

	cout<<"first completion time = "<<p[0].getct()<<"\n\n\n";

	sjf( p , 5 );
	print_process( p , 5 );

	return 0;
}