/*
Andrés Teruel Fernández

Escribir un programa que bloquee las señales SIGINT y SIGTSTP. Después de bloquearlas el programa debe suspender su ejecución con sleep(3) un número de segundos que se obtendrán de la variable de entorno SLEEP_SECS. 

Después de despertar de sleep(3), el proceso debe informar de si recibió la señal SIGINT y/o SIGTSTP. En este último caso, debe desbloquearla con lo que el proceso se detendrá y podrá ser reanudado en la shell (imprimir una cadena antes de finalizar el programa para comprobar este comportamiento).
*/

/*
Comentarios: me da error conseguir el valor de SLEEP_SECS,  a lo mejor es porque estoy 
desarrollando el código en una distribución de ubuntu que me descargué yo y no en la máquina virtual,
aún asi dejo comentado el código

*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	
	sigset_t blk_set;
	
	sigemptyset(&blk_set);
	sigaddset(&blk_set, SIGINT);
  	sigaddset(&blk_set, SIGTSTP);
	
	if(sigprocmask(SIG_BLOCK, &blk_set, NULL) == -1){
	
		perror("Error en la llamada a sigprocmask");
		return -1;
	}
	
	
	/*char *secsToSleep;

	secsToSleep = getenv("SLEEP_SECS");
	
	Hay que hacer la conversión a entero con atoi(3)
	*/
	
	int secsToSleep = 30;
	
	printf("El proceso se va a dormir.\n");
	sleep(30);
	printf("El proceso se despierta.\n");
	
	sigset_t pending_set;
	
	if(sigpending(&pending_set) == -1){
	
		perror("Error en la llamada a sigpending");
		return -1;
	}

	if(sigismember(&pending_set, SIGINT) == 1)
		printf("El proceso ha recibido la señal SIGINT\n");
		
	else
		printf("El proceso no ha recibido la señal SIGINT\n");	
		
		
	if(sigismember(&pending_set, SIGTSTP) == 1){
	
		printf("El proceso ha recibido la señal SIGTSTP\n");
	
		sigdelset(&blk_set, SIGINT);
		sigprocmask(SIG_UNBLOCK, &blk_set, NULL);
	}
	else
		printf("El proceso no ha recibido la señal SIGTSTP\n");	
	
	
	printf("acabando el programa...\n");
	return 0;
}
