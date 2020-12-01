#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#define MAX_INFO 3


//f(3), información de configuración del sistema de ficheros e imprima, por ejemplo,  el número máximo de enlaces, el tamaño máximo de una ruta y el de un nombre de fichero.

int main(){
	
	errno = 0;
	int info[MAX_INFO] = {_PC_LINK_MAX, _PC_PATH_MAX, _PC_NAME_MAX};
	long int aux;
	
	for(int i = 0; i < MAX_INFO; ++i){
	
		aux = pathconf("/", info[i]);
		
		if(aux == -1){
		
			if(errno == 0)
				printf("Error en la llamada a pathconf: Argumento es un límite indeterminado.\n");
			
			else
				perror("Error en la llamada a pathconf");
				
			return -1;
		}
		else
			printf("Informacion de la opcion '%d': %ld.\n", info[i], aux);
	}
	
	return 0;
}
