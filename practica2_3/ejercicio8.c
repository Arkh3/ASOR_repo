/*
Andrés Teruel Fernández

Usando la versión con execvp(3) del ejercicio 7 y la plantilla de demonio del ejercicio 6, escribir un programa que ejecute cualquier programa como si fuera un demonio. Además, redirigir los flujos estándar asociados al terminal usando dup2(2):
La salida estándar al fichero /tmp/daemon.out.
La salida de error estándar al fichero /tmp/daemon.err.
La entrada estándar a /dev/null.
Comprobar que el proceso sigue en ejecución tras cerrar la shell.*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <fcntl.h>

int redirigirSalidas(){

	int fd1,fd2,fd3;

	fd1 = open("/tmp/daemon.out", O_CREAT | O_RDWR, 0777);
	fd2 = open("/tmp/daemon.err", O_CREAT | O_RDWR, 0777);
	fd3 = open("/dev/null", O_CREAT | O_RDWR, 0777);

	dup2(fd1, 1);
	dup2(fd2, 2);
	dup2(fd3, 0);
}

int main(int argc, char *argv[]){

	if(argc == 1){
	
		printf("Usage: ./ejercicio7_2.c <comando>\n");
		return -1;
	}

	pid_t pid, sid;
	
	pid = fork();	
	
	int status;
	
	switch(pid){
	
		case -1:
			perror("Error en la llamada a fork");
			return -1;
		
		case 0:
		
			printf("Demonio: \n\n");
			
			// cambiar sesion, como es un hijo nos aseguramos que no es el lider en un grupo de procesos (y puede crear una sesiond)
			if((sid = setsid()) == -1){
			
				perror("Error en la llamada a setsid");
				return -1;
			}

			redirigirSalidas();
			printf("salidas redirigidas!\n");
	
			if(execvp(argv[1], argv + 1) == 1){
			
				perror("La llamada a execvp ha fallado");
				return -1;
			}

			break;
	
		default:
			
			if (wait(&status) == -1){
			
				perror("Error en la llamada a wait");
				return -1;
			}
			
			printf("Padre: ya ha acabado el hijo.\n");
	}
	
	return 0;
}
