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
		
    	int errsv = errno; 
		printf("Error %d: %s\n", errsv, strerror(errsv));
		ret = -1;
	}
	
	return ret;
}

