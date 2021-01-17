/*
Andrés Teruel Fernández

Crear otra tubería con nombre. Escribir un programa que espere hasta que haya datos listos para leer en alguna de ellas. El programa debe mostrar la tubería desde la que leyó y los datos leídos. Consideraciones: 
Para optimizar las operaciones de lectura usar un buffer (ej. de 256 bytes).
Usar read(2) para leer de la tubería y gestionar adecuadamente la longitud de los datos leídos.
Normalmente, la apertura de la tubería para lectura se bloqueará hasta que se abra para escritura (ej. con echo 1 > tuberia). Para evitarlo, usar la opción O_NONBLOCK en open(2).
Cuando el escritor termina y cierra la tubería, read(2) devolverá 0, indicando el fin de fichero, por lo que hay que cerrar la tubería y volver a abrirla. Si no, select(2) considerará el descriptor siempre listo para lectura y no se bloqueará.

*/
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){

	int fd1 = open("tuberia", O_RDONLY | O_NONBLOCK);
	int fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
	
	if(fd1 == -1 || fd2 == -1){
	
		perror("error abriendo las tuberias");
		close(fd1);
		close(fd2);
		return -1;
	}

	fd_set set;
	
	FD_ZERO(&set);
	FD_SET(fd1, &set);
	FD_SET(fd2, &set);
	
	char buf[256];
	int tamBuf = 0;
	
	int max = fd1;
	
	if(fd2 > fd1)
		max = fd2;
	
	max++;
	
	int cambios = select(max, &set, NULL, NULL, NULL);

	if (cambios == -1){
	
    	perror("select");
    	
    	close(fd1);
		close(fd1);
    	return -1;
    }
    else if (cambios == 1) {
   		
    	if(FD_ISSET(fd1, &set)){
    	
    		tamBuf = read(fd1, buf, 256);
    		buf[tamBuf] = '\0';
    		
    		printf("tuberia: %s\n", buf);
    		
    	}else{
    	
    	    read(fd2, buf, 255);
    		printf("tuberia2: %s\n", buf);
    	}
    } 

	close(fd1);
	close(fd1);
	
	return 0;
}
