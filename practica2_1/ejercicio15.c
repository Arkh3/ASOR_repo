/*Amdrés Teruel Fernández

Modificar el programa anterior para que imprima la hora de forma legible, como "lunes, 29 de octubre de 2018, 10:34", usando la función strftime(3).
*/

#include <time.h>
#include <stdio.h>


int main(){

	time_t t = time(NULL);
	
	if(t == ((time_t) -1)){
 	
 		perror("La llamada a time ha fallado");
 	
 		return -1;
 	}

	struct tm *info;
	
	info = localtime(&t);
	
	if(!info){
	
		perror("La llamada a localtime ha fallado");
		return -1;
	}
	else
		printf("%s", asctime(info));
	
	return 0;
}
