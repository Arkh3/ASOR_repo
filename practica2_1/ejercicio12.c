#include <time.h>
#include <stdio.h>


int main(){
 
 	int ret = 0;
 
 	time_t t = time(NULL);
 
 	if(t == ((time_t) -1)){
 	
 		perror("La llamada a time ha fallado");
 	
 		ret = -1;
 	}
	else
		printf("La hora en segundos desde Epoch es: %ld\n", t);
	
	return ret;
}
