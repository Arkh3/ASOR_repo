/*
Andrés Teruel Fernández

Escribir un programa que instale un manejador sencillo para las señales SIGINT y SIGTSTP. El manejador debe contar las veces que ha recibido cada señal. El programa principal permanecerá en un bucle que se detendrá cuando se hayan recibido 10 señales. El número de señales de cada tipo se mostrará al finalizar el programa. 
*/


//declarar las variables globales como volatile

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>


volatile int cont_sigint = 0;
volatile int cont_sigtstp = 0;


void handler(int signal){

	if (signal == SIGINT) 
		cont_sigint++;
		
  	if (signal == SIGTSTP) 
  		cont_sigtstp++;
}


int main(){

	struct sigaction action, action2;
	
	sigaction(SIGINT, NULL, &action);
	action.sa_handler = handler;
	sigaction(SIGINT, &action, NULL);

	sigaction(SIGTSTP, NULL, &action2);
	action2.sa_handler = handler;
	sigaction(SIGTSTP, &action2, NULL);
	
	while(cont_sigint + cont_sigtstp < 10){}
	
	printf("SIGINT se ha recibido %d veces.\n", cont_sigint);
	printf("SIGTSTP se ha recibido %d veces.\n", cont_sigtstp);
	
	return 0;
}
