/*
Andrés Teruel Fernández


Escribir un programa que muestre la política de planificación (como cadena) y la prioridad del proceso actual, además de mostrar los valores máximo y mínimo de la prioridad para la política de planificación. 
*/

/*Ejercicio3: probar con: sudo chrt -f 12 ./ejecutable*/

#include <sched.h>
#include <stdio.h>

int main(){

	int policy;
	if ((policy = sched_getscheduler(0)) == -1){
	
		perror("Error en la llamada a sched_getscheduler");
		return -1;
	}
	
	printf("Politica: ");
	
	switch(policy){
	
	case SCHED_OTHER: printf("SCHED_OTHER\n"); break;
	
	case SCHED_FIFO: printf("SCHED_FIFO\n"); break;
	
	case SCHED_RR: printf("SCHED_RR\n"); break;
	
	default: printf("Unknown\n");
	}

	struct sched_param prioridad;
	
	if(sched_getparam(0, &prioridad) == -1){
	
		perror("Error en la llamada a sched_getparam");
		return -1;
	}
	
	printf("Prioridad: %d\n", prioridad.sched_priority);
	
	int max,min;
	
	if ((max = sched_get_priority_max(policy)) == -1){
	
		perror("Error en la llamada a sched_get_priority_max");
		return -1;
	}

	if ((min = sched_get_priority_min(policy)) == -1){
	
		perror("Error en la llamada a sched_get_priority_min");
		return -1;
	}
	
	printf("Rango de prioridades de la politica-> min: %d max: %d\n", min, max);

	return 0;
} 
