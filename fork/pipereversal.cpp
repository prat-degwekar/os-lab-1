#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    int fd[2];
    int val = 0;

    // create pipe descriptors
    pipe(fd);

    // fork() returns 0 for child process, child-pid for parent process.

    if (fork() != 0)
    {
        // parent: writing only, so close read-descriptor.

        close(fd[0]);

        // send the value on the write-descriptor.

        val = 250;

        char buff[15] = "malayalam";

        write(fd[1], buff, sizeof(buff));

        printf("\n\nParent(%d) send value: %s\n", getpid(), buff);

        // close the write descriptor

        close(fd[1]);
    }

    else
    {   

        // child: reading only, so close the write-descriptor

        close(fd[1]);

        char buff[35] = "";

        // now read the data (will block)

        read(fd[0], buff, sizeof(buff));

        //string str(buff);

        printf("\n\nChild(%d) received value: %s\n", getpid(), buff);

        string str(buff);

        string revstr = str;

        reverse( revstr.begin() , revstr.end() );

        cout<<"\n\n\treversed string : "<<revstr<<endl;

        int kk = revstr.compare(str);

        if( kk == 0 )
        {
            cout<<"\n\n\tThe string is a Pallindrome!\n\n";
        }

        else
        {
            cout<<"\n\n\tthe String is NOT a pallindrome...\n\n";
        }

        // close the read-descriptor

        close(fd[0]);
    }

    return 0;
}