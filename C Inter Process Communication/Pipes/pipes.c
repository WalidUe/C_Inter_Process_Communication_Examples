#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

	int pipefd[2];
	int pid;
	char recv[32];

	pipe(pipefd);

	switch(pid = fork())
	{
		case -1:
			perror("fork");
			exit(1);
		case 0:				//In child process
			close(pipefd[0]);	//close read fd
			FILE *out = fdopen(pipefd[1],"w"); //open pipe descriptor as stream
			fprintf(out, "Hello World \n");	   //write to out stream
			break;
		default:			//In parent process
			close(pipefd[1]);	//close write fd
			FILE *in = fdopen(pipefd[0], "r"); //open descriptor as stream
			fscanf(in, "%s", recv);		//read from in stream
			printf("%s \n", recv);
			break;
	}



}