//para perror y strerror
#include <stdio.h>
#include <errno.h>
#include <string.h>
//execl
#include <stdlib.h>

#define MAX_ERRORES 255


int main(){
	
	for(int i = 0; i < MAX_ERRORES; ++i)
		printf("El mensaje asociado al error '%d' es: %s.\n", i, strerror(i));

	/*puedes comentar la parte de arriba y descomentar la linea de abajo pero para poder
	ejecutar el comando "errno -l" necesitas el paquete moreutils*/
	//system("errno -l");
		
	return 0;
}

