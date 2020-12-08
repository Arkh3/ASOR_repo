/*
Andrés Teruel Fernández

Escribir un programa que, usando la llamada open(2), cree un fichero con los permisos rw-r--r-x. Comprobar el resultado y las características del fichero con la orden ls.
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <stdio.h>

int main (int argc, char *argv[]){

	//hacer una entrada con el nombre del fichero a crear
	
	if(argc == 1){
	
		printf("Usage: ./ejercicio5.c <filename>\n");
		return -1;
	}
	
	
	int fd;
	
	fd = open(argv[1] , O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IXOTH);
	
	if(fd == -1){
	
		perror("Error en la llamada a open(2)");
		return -1;
	}

	printf("El fichero se ha creado con exito!\n");
	
	return 0;
}

