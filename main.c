#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#define MY_SEM 21

int main(int argc, char** argv) {
	
	if (argc < 2) {
		fprintf(stderr, "Invalid number of args\n");
		exit(1);
	}
	
	int key;
	if (argv[1][0] == '-' && strlen(argv[1]) > 1) {
		switch(argv[1][1]) {
			case 'c':
				key = semget(MY_SEM, 1, IPC_CREAT | IPC_EXCL | 0600);
				if (key == -1 && errno == EEXIST) {
					printf("semaphore exists\n");
					exit(1);
				}
				
				semctl(key, 0, SETVAL, atoi(argv[2]));
				printf("Adding semaphore: %d\n", key);
			break;
			
			case 'v':
				key = semget(MY_SEM, 1, 0600);
				printf("semaphore val: %d\n", semctl(key, 0, GETVAL));
			break;
			
			case 'r':
				key = semget(MY_SEM, 1, 0600);
				semctl(key, 0, IPC_RMID);
				printf("Removed semaphore\n");
			break;
		}
	}
	else {
		fprintf(stderr, "Please enter a flag\n");
		exit(1);
	}
	
	return 0;
}
