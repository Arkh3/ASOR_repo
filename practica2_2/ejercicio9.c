/*
Andrés Teruel Fernández

 Escribir un programa que emule el comportamiento del comando stat y muestre:
El número major y minor asociado al dispositivo.
El número de i-nodo del fichero.
El tipo de fichero (directorio, enlace simbólico o fichero ordinario).
La hora en la que se accedió el fichero por última vez. ¿Qué diferencia hay entre st_mtime y st_ctime?
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(int argc, char *argv[]){


	if(argc == 1){
	
		printf("Usage: %s <filename>\n", argv[0]);
		return -1;
	}
	
	struct stat file_data;

	if (stat(argv[1], &file_data) == -1){
	
		perror("La llamada a stat(2) ha fallado");
		return -1;
	}



	unsigned int maj = major(file_data.st_dev);
	unsigned int min = minor(file_data.st_dev);
	
	char *fileType;
	fileType = malloc(sizeof(char)*50);
	
   	if (file_data.st_mode & S_IFMT == S_IFREG)
   		fileType = "fichero ordinario";
   		
   	else if (file_data.st_mode & S_IFMT == S_IFLNK)
   		fileType = "enlace simbolico";
   	
   	else if (file_data.st_mode & S_IFMT == S_IFDIR)
   		fileType = "directorio";
   		
   	else
   		fileType = "unknown";
   	
   	printf("major: %d\tminor: %d\ni_node: %ld\ttipo de fichero: %s\n", maj, min, /*(long) */ file_data.st_ino, fileType);

   	printf("fecha de ultimo acceso: %s\n", ctime(&file_data.st_atime));

	return 0;
}
