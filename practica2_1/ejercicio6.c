#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#define MAX_INFO 3

int main(){
	
	errno = 0;
	int info[MAX_INFO] = {_SC_ARG_MAX, _SC_CHILD_MAX, _SC_OPEN_MAX};
	long int aux;
	
	for(int i = 0; i < MAX_INFO; ++i){
	
		aux = sysconf(info[i]);
		
		if(aux == -1){
		
			if(errno == 0)
				printf("Error en la llamada a sysconf: Argumento es un límite indeterminado.\n");
			
			else
				perror("Error en la llamada a sysconf");
				
			return -1;
		}
		else
			printf("Informacion de la opcion '%d': %ld.\n", info[i], aux);
	}
	
	return 0;
}
