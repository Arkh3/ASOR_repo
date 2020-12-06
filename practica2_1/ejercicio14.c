/*Amdrés Teruel Fernández

 Escribir un programa que muestre el año usando la función localtime(3).
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
		printf("El año actual es: %d\n", info->tm_year + 1900);
	
	return 0;
}
