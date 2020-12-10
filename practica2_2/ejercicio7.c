/*
Andrés Teruel Fernández

Modificar el ejercicio 5 para que, antes de crear el fichero, se fije la máscara igual que en el ejercicio 6. Comprobar el resultado con el comando ls. Comprobar que la máscara del proceso padre (la shell) no cambia.
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <stdio.h>

int main (int argc, char *argv[]){

	//hacer una entrada con el nombre del fichero a crear
	
	umask(727);

	
	if(argc == 1){
	
		printf("Usage: ./ejercicio7.c <filename>\n");
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

