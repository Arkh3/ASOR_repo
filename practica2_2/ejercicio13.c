/*
Andrés Teruel Fernández

Modificar el programa anterior para que además de escribir en el fichero la salida estándar también se escriba la salida estándar de error. Comprobar el funcionamiento incluyendo varias sentencias que impriman en ambos flujos. ¿Hay alguna diferencia si las redirecciones se hacen en diferente orden? ¿Por qué no es lo mismo “ls > dirlist 2>&1” que “ls 2>&1 > dirlist”?
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]){

	if(argc != 2){
		
		printf("Usage: %s <filename>", argv[0]);
		return -1;
	}
	
	int fd = open(argv[1], O_CREAT | O_RDWR, 0777);

	if(fd == -1){
	
		perror("Fallo en la llamada open");
		return -1;
	}
	
	dup2(fd, 1);
	dup2(fd, 2);
	
	fprintf(stderr, "Esto debería ir a la salida de error pero se redirige\n");
	printf("Esta cadena se rediccionará al fichero %s.\n", argv[1]);
	fprintf(stderr, "Esta cadena es la segunda cadena que deberia ir a error\n");
	printf("Y esta tambien!\n");
	
	return 0;
}

/*Al parecer primero se redirigen las cadenas destinadas a la salida de error y luego las cadenas destinadas a la salida estandar*/
