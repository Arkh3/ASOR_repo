/*
Andrés Teruel Fernández

Escribir un programa que emule el comportamiento de la shell en la ejecución de una sentencia en la forma: comando1 argumento1 | comando2 argumento2. El programa creará una tubería sin nombre y creará un hijo:

El proceso padre redireccionará la salida estándar al extremo de escritura de la tubería y ejecutará comando1 argumento1.

El proceso hijo redireccionará la entrada estándar al extremo de lectura de la tubería y ejecutará comando2 argumento2.

Probar el funcionamiento con una sentencia similar a: ./ejercicio1 echo 12345 wc -c

Nota: Antes de ejecutar el comando correspondiente, deben cerrarse todos los descriptores no necesarios.

*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char *argv[]){

	if(argc < 5){
	
		printf("Usage: %s <comando1> <argumento1> <comando2> <argumento2>\n", argv[0]);
		return -1;
	}
	
	int fd[2];
		
	if(pipe(fd) == -1){
	
		perror("pipe");
		return -1;
	}
		
	pid_t pid = fork();
	
	switch(pid){
	
		case -1:
		
			perror("fork");
			return -1;

		case 0:
			
			close(fd[1]);
		
			if(dup2(fd[0], 0) == -1){
			
				perror("primer dup2");
				return -1;
			}
			
			char* comm2 = malloc(sizeof(char)*255);
			strcpy(comm2, argv[3]);
			strcat(comm2, " ");
			strcat(comm2, argv[4]);

			close(fd[0]);
			
			system(comm2);

			break;
			
		default:
		
			close(fd[0]);
		
			if(dup2(fd[1], 1) == -1){
			
				perror("segundo dup2");
				return -1;
			}
		
			char* comm = malloc(sizeof(char)*255);
			strcpy(comm, argv[1]);
			strcat(comm, " ");
			strcat(comm, argv[2]);
			
			close(fd[1]);
			
			system(comm);
	}
	

	return 0;
}
