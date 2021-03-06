#include <string>
#include <string.h>
#include <iostream>

using namespace std;

class process
{

private:
	int at;
	int ct;
	int tat;
	string pid;
	int bt;
	int wt;
	int pr;

public:

	//constructor

	process()
	{
		ct = -1;
	}

	process(int bat , int bbt , int bpr , string bpid)
	{
		at = bat;
		bt = bbt;
		pid = bpid;
		ct = -1;
		wt = 0;
		pr = bpr;
	}

	int getat()
	{
		return at;
	}

	int getbt()
	{
		return bt;
	}

	int getwt()
	{
		return wt;
	}

	int getpr()
	{
		return pr;
	}

	int gettat()
	{
		return tat;
	}

	int getct()
	{
		return ct;
	}

	string getpid()
	{
		return pid;
	}

	void setat(int bat)
	{
		at = bat;
	}

	void setbt(int bbt)
	{
		bt = bbt;
	}

	void setwt(int bwt)
	{
		wt = bwt;
	}

	void setct(int bct)
	{
		ct = bct;
		//cout<<"ct set to : "<<ct<<endl;
	}

	void caltat()
	{
		tat = ct - at;
	}

	void calwt()
	{
		wt = ct - bt;
	}

	void setpr( int bpr )
	{
		pr = bpr;
	}

	void setpid(string bpid)
	{
		pid = bpid;
	}

};

void fcfs( process[] , int );

void sjf( process[] , int );

void print_process( process[] , int );

void srt( process[] , int );

void rr( process[] , int );

void hrr( process[] , int );

void prp( process[] , int );

void prnp( process[] , int );

void exc( process[] , int );