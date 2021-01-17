/*
Andrés Teruel Fernández

Escribir un programa que abra la tubería con el nombre anterior en modo sólo escritura, y escriba en ella el primer argumento del programa. En otro terminal, leer de la tubería usando un comando adecu

*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){

	int fd1 = open("tuberia", O_WRONLY);
	
	if(fd1 == -1){
	
		perror("open");
		return -1;
	}
	
	size_t len = strlen(argv[0]);
	
	write(fd1, argv[0], len);
	
	close(fd1);
	
	printf("Se ha leido todo\n");
}
