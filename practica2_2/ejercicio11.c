/*
Andrés Teruel Fernández

Las llamadas link(2) y symlink(2) crean enlaces rígidos y simbólicos, respectivamente. Escribir un programa que reciba una ruta a un fichero como argumento. Si la ruta es un fichero regular, creará un enlace simbólico y rígido con el mismo nombre terminado en .sym y .hard, respectivamente. Comprobar el resultado con la orden ls.
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char *argv[]){

	if(argc == 1){
	
		printf("Usage: %s <filename>\n", argv[0]);
		return -1;
	}
	
	struct stat file_data;

	if (stat(argv[1], &file_data) == -1){
	
		perror("La llamada a stat() ha fallado");
		return -1;
	}
	
	if ((file_data.st_mode & S_IFMT) == S_IFREG){
	
		char nombre_sym[300];
		
		strcpy(nombre_sym, argv[1]); 
		strcat(nombre_sym, ".sym");
		
		char nombre_hard[300];
		
		strcpy(nombre_hard, argv[1]); 
		strcat(nombre_hard, ".hard");

		if( link(argv[1], nombre_hard)== -1){
		
			perror("Error en la llamada a link()");
			return -1;
		}
		
		if( symlink(argv[1], nombre_sym)== -1){
		
			perror("Error en la llamada a symlink()");
			return -1;
		}	
	}

	printf("Los enlaces se han creado con exito!\n");
	
	return 0;
}
