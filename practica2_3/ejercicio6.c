/*
Andrés Teruel Fernández

Un demonio es un proceso que se ejecuta en segundo plano para proporcionar un servicio. Normalmente, un demonio está en su propia sesión y grupo. Para garantizar que es posible crear la sesión y el grupo, el demonio crea un nuevo proceso para ejecutar la lógica del servicio y crear la nueva sesión. Escribir una plantilla de demonio (creación del nuevo proceso y de la sesión) en el que únicamente se muestren los atributos del proceso (como en el ejercicio anterior). Además, fijar el directorio de trabajo del demonio a /tmp.
¿Qué sucede si el proceso padre termina antes que el hijo (observar el PPID del proceso hijo)? ¿Y si el proceso que termina antes es el hijo (observar el estado del proceso hijo con ps)?
Nota: Usar sleep(3) o pause(3) para forzar el orden de finalización deseado.
*/

/*Un si el proceso padre acaba despues, con el comando ps podemos ver que el Demonio se queda en estado Z o estado zombie (el proceso ya no existe pero deja su entrada en la tabla de procesos para el padre)*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/resource.h>

#define SIZE 256

int infoProceso(){

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

int main(){

	pid_t pid, sid;
	
	pid = fork();	
	
	int status;
	
	switch(pid){
	
		case -1:
			perror("Error en la llamada a fork");
			return -1;
		
		case 0:
		
			
			printf("Demonio: \n\n");
			
			if(chdir("/tmp") == -1){
			
				perror("Error en la llamada a chdir");
				return -1;
			}	
			
			// cambiar sesion, como es un hijo nos aseguramos que no es el lider en un grupo de procesos (y puede crear una sesiond)
			if((sid = setsid()) == -1){
			
				perror("Error en la llamada a setsid");
				return -1;
			}


			//esta parte he querido hacerla con execl pero no me ha salido
			if(infoProceso() == -1){
			
				perror("Error en la llamada a execlp");
				return -1;
			}
			
			break;
	
		default:
			
			//sleep(3);
			
			if (wait(&status) == -1){
			
				perror("Error en la llamada a wait");
				return -1;
			}
			
			printf("Padre: ya ha acabado el hijo.\n");
			
			
	}
	
	return 0;
}
