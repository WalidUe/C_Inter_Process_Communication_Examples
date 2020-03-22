#include  <sys/types.h>

#include  <sys/ipc.h>

#include  <sys/shm.h>

#include  <stdio.h>

#include  <stdlib.h>

#include <unistd.h>



#define SHMSIZE 27 //size of the shared memory



int main()

{



	char c;

	int shmid;

	key_t key;

	char *shm, *s;



	key = 5678;//some key to uniquely identify the shared memory

	

	//Creating the segment

	if((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) <0)

	{



	perror("shmget");

	exit(1);

	}



	//Attach the segment to our data space

	if((shm = shmat(shmid, NULL, 0)) == (char *) -1)

	{

		perror("shmat");

		exit(1);

	}

	

	//Putting some data into the shared memory

	s = shm;

	for(c = 'a'; c<='z';c++)

		*s++ = c;

	*s = 0;//end with a NULL termination



	//wait until the other process changes the first character

	//to '*'

	while(*shm != '*')

		sleep(1);

	





return 0;



}

