/*
Andrés Teruel Fernández

Escribir un programa que redirija la salida estándar a un fichero cuya ruta se pasa como primer argumento. Probar haciendo que el programa escriba varias cadenas en la salida estándar.
*/

#include <stdio.h>
#include <unistd.h>
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
	
	dup2(fd, 1);
	
	printf("Esta cadena se rediccionará al fichero %s.\n", argv[1]);
	printf("Y esta tambien!\n");
	
	return 0;
}
