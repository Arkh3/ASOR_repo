/*
Andrés Teruel Fernández

Escribir un programa que realice el borrado programado del propio ejecutable. El programa tendrá como argumento el número de segundos que esperará antes de borrar el fichero. El borrado del fichero se podrá detener si se recibe la señal SIGUSR1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int stop = 0;


void handler(int signal){

	if(signal == SIGUSR1)
		stop = 1;
}

int main(int argc, char *argv[]){


	if(argc != 2){
	
		printf("Usage: ./ejercicio13 <segs>\n");
		return -1;
	}
	
	
	struct sigaction action;
	
	sigaction(SIGUSR1, NULL, &action);
	action.sa_handler = handler;
	sigaction(SIGUSR1, &action, NULL);


	int secs;
	secs = atoi(argv[1]);
	
	int i = 0;
	
	while(i < secs && stop == 0){
	
		printf("%d...\n", secs - i);
	
		sleep(1);
		++i;
	}
	
	if(stop == 1)	
		printf("El ejecutable no se va a borrar.\n");
	
	else{

		unlink(argv[0]);
		printf("El ejecutable se ha borrado.\n");
	}
	
	return 0;	
}
