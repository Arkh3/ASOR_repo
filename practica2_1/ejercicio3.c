//para perror y strerror
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define MAX_ERRORES 255


int main(){
	
	for(int i = 0; i < MAX_ERRORES; ++i)
		printf("El mensaje asociado al error '%d' es: %s.\n", i, strerror(i));
	
	return 0;
}

