#include  <sys/types.h>

#include  <sys/ipc.h>

#include  <sys/shm.h>

#include  <stdio.h>

#include  <stdlib.h>



#define SHMSIZE 27 //size of the shared memory



int main()

{



	

	int shmid;

	key_t key;

	char *shm, *s;



	key = 5678;//get the segment named 5678 created by the server

	

	//Locate the segment

	if((shmid = shmget(key, SHMSIZE, 0666)) <0)

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

	

	//Reading what the server put in the memory

	

	for(s = shm; *s != 0;s++)

		putchar(*s);

	putchar('\n');



	//Finally, change the first character of the segment to '*'

	//indicating we have read the segment

	*shm = '*';

		

	





return 0;



}

