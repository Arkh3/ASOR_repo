/*
Andrés Teruel Fernández

Escribir un programa que consulte y muestre en pantalla el estado del cerrojo sobre un fichero. El programa mostrará el estado del cerrojo (bloqueado o desbloqueado). Además:
-Si está desbloqueado, fijará un cerrojo y escribirá la hora actual. Después suspenderá su ejecución durante 30 segundos (con sleep(3)) y a continuación liberará el cerrojo.
-Si está bloqueado, terminará el programa.
*/
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main(int argc, char *argv[]){

	if(argc != 2){
		
		printf("Usage: %s <filename>", argv[0]);
		return -1;
	}
	
	int fd = open(argv[1], O_CREAT | O_RDWR, 0777);

	if(fd == -1){
	
		perror("Fallo en la llamada open");
		return -1;
	}

	//consultar el estado del cerrojo 
	int estado = lockf(fd, F_TLOCK, 3);
	
	if(estado != -1){
	
		//escribir la hora actual
		time_t aux;
		  
		struct tm *timeinfo;

		time(&aux);
		timeinfo = localtime(&aux);
		printf ("Hora actual: %dh %dmin %ds\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
		
		//suspender 30 segundos
		sleep(30);
		
		//desbloquear el fichero
		lockf(fd, F_UNLCK, 0);
	
	}
	else
		printf("El cerrojo estaba bloqueado\n");
	
	return 0;
}
