#include  <stdio.h>
#include  <sys/types.h>
#include  <string.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <sys/wait.h>
#include  <fstream>
#include  <iostream>
#include  <string>
#include  <cstdio>

using namespace std;

int indlux = 0;

void  parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;             /* skip the argument until ...    */
     }
     *argv = '\0';                 /* mark the end of argument list  */
}

void  execute(char **argv , string line)
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0)
     {          /* for the child process:         */

          int len = strlen(argv[0]);
          cout<<"len = "<<len<<endl;
          cout<<argv[0]<<endl;

          if(argv[0][len-1] == '!')
          {
               cout<<"well, heres a hist instance.\n\n";
               string str = line.substr(0,len-1);
               int gk = atoi(str.c_str());
               cout<<"string int is : "<<gk<<endl;

               //read file

               ifstream ifile;
               ifile.open("history.txt");

               int strt = indlux - gk;

               cout<<"reached here also\n\n";

               while(!ifile.eof())
               {
                    int tempint;
                    string tempstring;
                    string tmp;
                    getline(ifile , tempstring);
                    tempint = atoi(tempstring.c_str());
                    //ifile>>tempint;
                    getline( ifile , tmp );
                    cout<<tmp<<endl;
                    //cin>>tempint;
                    if(tempint < strt)
                    {
                         //cout<<"in cont blok\n";
                         continue;
                    }
                    cout<<tmp<<endl;
               }

               ifile.close();

               //end file read

               exit(1);
          }

          if (execvp(*argv, argv) < 0) {     /* execute the command  */
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else 
     {                                  /* for the parent:      */
          while (wait(&status) != pid);       /* wait for completion  */
          //insert file writing here
          ofstream ofile;
          cout<<"\nhere\n";
          ofile.open("history.txt" , ios::out | ios::app );
          ofile<<indlux<<"\n"<<line<<"\n";
          //<<*argv<<"\n"<<argv<<"\n";
          //cout<<"\n\n";
          ofile.close();
          //ofile.close();
          indlux++;
     }
}

int main(void)
{
     char  line[1024];             /* the input line                 */
     char  *argv[64];              /* the command line argument      */

     while (1) 
     {                   /* repeat until done ....         */
          printf("Shell -> ");     /*   display a prompt             */
          //fgets(line , sizeof(line) , stdin);              /*   read in the command line     */
          //gets(line);
          string lne;
          getline(cin , lne);
          strcpy(line , lne.c_str());
          printf("\n");
          parse(line, argv);       /*   parse the line               */
          if (strcmp(argv[0], "exit") == 0)  /* is it an "exit"?     */
               exit(0);            /*   exit if it is                */
          execute(argv , lne);           /* otherwise, execute the command */
     }

     return 0;
}