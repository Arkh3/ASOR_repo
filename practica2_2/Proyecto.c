/*
Andrés Teruel Fernández

Escribir un programa que cumpla las siguientes especificaciones:
-El programa tiene un único argumento que es la ruta a un directorio. El programa debe comprobar la corrección del argumento.
-El programa recorrerá las entradas del directorio de forma que:

	*Si es un fichero normal, escribirá el nombre.
	*Si es un directorio, escribirá el nombre seguido del carácter ‘/’.
	*Si es un enlace simbólico, escribirá su nombre seguidoq de ‘->’ y el nombre del fichero enlazado. Usar readlink(2) y dimensionar adecuadamente el buffer.
	*Si el fichero es ejecutable, escribirá el nombre seguido del carácter ‘*’.
	
-.Al final de la lista el programa escribirá el tamaño total que ocupan los ficheros (no directorios) en kilobytes.
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

/*Notas: no he sabido como hacer que distinga cuando es un ejecutable*/

int main(int argc, char *argv[]){

	if(argc != 2){
		
		printf("Usage: %s <directorypath>\n", argv[0]);
		return -1;
	}
	
	DIR *d;

	d = opendir(argv[1]);
	
	if(!d){
	
		perror("Error en la llamada a opendir");
		return -1;
	}

	struct dirent *entrada;
	struct stat stats;
	long int tamFiles = 0;
	
	entrada = readdir(d);

	while(entrada){
	
		char *path = malloc(sizeof(char)*256);
		
		char *nombre_l = malloc(sizeof(char)*256);
		strcpy(path, argv[1]);
		strcat(path, "/");
		strcat(path, entrada->d_name);
		strcat(path, "\0");
	
		if(stat(path, &stats) == -1){
		
			perror("Error a la llamada a stat");
			return -1;
		}
		
		if((S_IXUSR & stats.st_mode || S_IXGRP & stats.st_mode || S_IXOTH & stats.st_mode) && (entrada->d_type != DT_DIR)){
		
			printf("%s*\n", entrada->d_name);
			tamFiles += stats.st_size/1000;
		}
		else{
		
			switch(entrada->d_type){
			
			case DT_REG:
			printf("%s\n", entrada->d_name);
			tamFiles += stats.st_size/1000; break;
			
			case DT_DIR:
			printf("%s/\n", entrada->d_name); break;
			
			case DT_LNK:
			
			if(readlink(path, nombre_l, stats.st_size + 1) == -1){
			
				perror("Error a la llamada a readlink");
				return -1;
			}
			
			printf("%s -> %s\n", entrada->d_name, nombre_l);
			
			tamFiles += stats.st_size/1000; break; 
			}
		}
		entrada = readdir(d);
	}
	
	printf("El tamaño total que ocupan los ficheros es de %ld kilobytes.\n", tamFiles);
	closedir(d);
	
	return 0;
}

