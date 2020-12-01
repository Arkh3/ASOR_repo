#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>


int main(){

	struct utsname * aux;
	aux = malloc(sizeof(*aux));
	
	if (uname(aux) == -1){
		
		perror("La llamada a uname ha fallado");
	}
	else{
	
		printf("Sistema operativo: %s.\nNodo: %s.\nFecha de lanzamiento: %s.\nVersión: %s.\nIdentificador hardware: %s.\n", aux->sysname, aux->nodename, aux->release, aux->version, aux->machine);
		
	}



	return 0;
}
