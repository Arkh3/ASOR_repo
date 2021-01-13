/*
Andrés Teruel Fernández

Escribir un programa que muestre los identificadores del proceso: identificador de proceso, de proceso padre, de grupo de procesos y de sesión. Mostrar además el número máximo de archivos que puede abrir el proceso y el directorio de trabajo actual.
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

#define SIZE 256

int main(){

	pid_t pid, ppid, gid, sid;
	struct rlimit limite;
	
	pid = getpid();
	ppid = getppid();
	
	if(gid = getpgid(0) == -1){
		
		perror("Error en la llamada a getpgid");
		return -1;
	}
	
	if(sid = getsid(0) == -1){
	
		perror("Error en la llamada a getsid");
		return -1;
	}
	
	if(getrlimit(RLIMIT_NOFILE, &limite) == -1){
	
		perror("Error en la llamada a getrlimit");
		return -1;
	}
	
	char buf[SIZE];
	
	if(!getcwd(buf, SIZE)){
		
		perror("Error en la llamada a getcwd");
		return -1;
	}
	
	printf("PID: %d\tParent PID: %d\tGroup ID:%d\tSession ID:%d\n", pid, ppid, gid,sid);
	printf("Numero maximo de archivos que puede abrir: %lu\n", limite.rlim_max);
	printf("Directorio de trabajo: %s\n", buf);

	return 0;
}
