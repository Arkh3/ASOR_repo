/*
Andrés Teruel Fernández

Para la comunicación bi-direccional, es necesario crear dos tuberías, una para cada sentido: p_h y h_p. Escribir un programa que implemente el mecanismo de sincronización de parada y espera:

El padre leerá de la entrada estándar (terminal) y enviará el mensaje al proceso hijo, escribiéndolo en la tubería p_h. Entonces permanecerá bloqueado esperando la confirmación por parte del hijo en la otra tubería, h_p.

El hijo leerá de la tubería p_h, escribirá el mensaje por la salida estándar y esperará 1 segundo. Entonces, enviará el carácter ‘l’ al proceso padre, escribiéndolo en la tubería h_p, para indicar que está listo. Después de 10 mensajes enviará el carácter ‘q’ para indicar al padre que finalice.
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){

	char* msg = malloc(sizeof(char)*255);
	char* confirmation = malloc(sizeof(char)*255);
	
	int cont = 0;
	
	int p_h[2];
	int h_p[2];
	
	if(pipe(p_h) == -1){
	
		perror("pipe");
		return -1;
	}
	
	if(pipe(h_p) == -1){
	
		perror("segundo pipe");
		return -1;
	}
	
	pid_t pid;
	pid = fork();
	
	switch (pid) {
	
	case -1:
		perror("fork");
		exit(1);
		
	case 0:
	
		close(p_h[1]);
		close(h_p[0]);
	
		while(cont < 10){
			
			read(p_h[0], msg, 255);
			printf("Hijo: el mensaje del padre es: %s\n", msg);
			
			++cont;
			
			if(cont < 10)
				write(h_p[1], "l", 2);
		}
		
		write(h_p[1], "q", 2);
		printf("Hijo: he acabado");
		
		close(p_h[0]);
		close(h_p[1]);
		
		break;
		
	default:
		
		close(p_h[0]);
		close(h_p[1]);
		
		while(confirmation != "q"){
		
			printf("Padre: Mensaje a enviar al hijo (): ");
			scanf("%s", msg);
			
			write(p_h[1], msg, 255);
			read(h_p[0], confirmation, 255);
		}
		
		close(p_h[1]);
		close(h_p[0]);
		
		break;
	}
	return 0;
}

