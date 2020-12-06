/*Andrés Teruel Fernández

Escribir un programa que mida, en microsegundos usando la función gettimeofday(2), lo que tarda un bucle que incrementa una variable un millón de veces.
*/
#include <stdio.h>
#include <sys/time.h>


int main(){
 
 	int ret = 0, inicio, fin;
	struct timeval times;

    if (gettimeofday(&times, NULL) == -1){
    
    	perror("La llamada a gettimeofday ha fallado");
    	ret = -1;	
    }
    else{
    
    
    	inicio = times.tv_usec;
    	
    	for(int i = 0; i < 1000000; ++i);
    	
    	 if (gettimeofday(&times, NULL) == -1){
    
			perror("La llamada a gettimeofday ha fallado");
			ret = -1;	
		}
		else{
		
			fin = times.tv_usec;
			
			
			printf("Un bucle que incrementa una variable un millon de veces tarda %d microsegundos.\n", fin - inicio);
		}
		
    }
	
    
	return ret;
}
