//para perror y strerror
#include <stdio.h>
#include <errno.h>
#include <string.h>
//para setuid
#include <sys/types.h>
#include <unistd.h>



int main(){

	int ret = 0;

	if(setuid(0) == -1){
		
		perror("La llamada a setuid ha fallado");
		ret = -1;
	}
	
	return ret;
}

