#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <iostream>

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

        char buff[70] = "helloxD I am a sentence. this is a new line.\nI am a new statement. ";

        write(fd[1], buff, sizeof(buff));

        printf("\n\nParent(%d) send value: %s\n", getpid(), buff);

        // close the write descriptor

        close(fd[1]);
    }
    else
    {   // child: reading only, so close the write-descriptor

        close(fd[1]);

        char buff[250] = "";

        read(fd[0], buff, sizeof(buff));

        int sz = sizeof(buff);

        int wc = 1 , sc = 0 , cc = 0 , lc = 1;

        for(int i=0 ; i<sz ; i++)
        {
            char k = buff[i];

            if(isalpha(k))
                cc++;

            if( k == ' ' )
                wc++;

            if( k == '.' )
                sc++;

            if( k == '\n' )
                lc++;
        }

        printf("\n\nChild(%d) received value: %s\n", getpid(), buff);

        cout<<"\n\nSTATS\n\n";

        cout<<"\tword count = "<<wc<<endl;

        cout<<"\tcharacter count = "<<cc<<endl;

        cout<<"\tsentence count = "<<sc<<endl;

        cout<<"\tline count = "<<lc<<endl;

        cout<<endl<<endl;

        // close the read-descriptor

        close(fd[0]);
    }
    return 0;
}