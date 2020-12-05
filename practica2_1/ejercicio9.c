#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(){

	printf("UID real del usuario: %d\nUID efectivo del usuario: %d\n", getuid(), geteuid());
	return 0;
} 
