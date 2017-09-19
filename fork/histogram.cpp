#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>
#include <ctype.h>
#include <string>
#include <string.h>
#include <sys/wait.h>

using namespace std;

int main()
{
	string str = "";

	char stringer[250] = "";
	

	cout<<"enter text : ";
	
	int pid = vfork();

	if(pid < 0)
	{
		cout<<"vfork error\n\n";
		exit(0);
	}
	else if(pid == 0)
	{
		//wait(getppid());
		string temp;

		do 
		{
			temp = "";
 			getline(cin, temp);
 			if(temp.length() == 0)
 				str += '\0';
 			else
 				str += temp + " ";

		}while (temp.length() > 0);

		cout<<"\n\nended input\ninput is : "<<str<<endl<<endl<<endl;
		strcpy(stringer , str.c_str() );
		//cout<<"stringer = "<<stringer<<endl;

		exit(0);

	}

	else
	{
		/*do 
		{
 			getline(cin, temp);
 			str += temp + "\n";

		} while (temp.length() > 0);*/

		wait(0);
		//sleep(5);
		//cout<<"stringer = "<<stringer<<endl;
		//cout<<"here\nlength = "<<str.length()<<"\n";

		int arr[26] = {0};

		for(int i=0 ; i<str.length() ; i++)
		{
			char ch = (char)str.at(i);
			
			if( !isalpha(ch) )
				continue;

			char kk = tolower(ch);
			int num = (int)(kk - 'a');
			arr[num]++;
			//cout<<"char = "<<ch<<endl;
			//cout<<"num = "<<num<<endl;
		}

		cout<<"\n\n\tdone counting";
		cout<<"\n\tSTATS\n\n";
		for(int i=0 ; i<26 ; i++)
		{
			if(arr[i] == 0)
				continue;
			char k = (char)('a' + i);
			cout<<"\t"<<k<<" : "<<arr[i]<<endl;
		}

		cout<<endl<<endl;

	}

	return 0;

}