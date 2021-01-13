/*
Andrés Teruel Fernández

Escribir dos versiones, una con system(3) y otra con execvp(3), de un programa que ejecute otro programa que se pasará como argumento por línea de comandos. En cada caso, se debe imprimir la cadena “El comando terminó de ejecutarse” después de la ejecución. ¿En qué casos se imprime la cadena? ¿Por qué? 

Nota: Considerar cómo deben pasarse los argumentos en cada caso para que sea sencilla la implementación. Por ejemplo: ¿qué diferencia hay entre ./ejecuta ps -el y ./ejecuta “ps -el”?
*/

/*
Respuesta: 

En el programa de system(3) si se imprime la frase del final ya que system hace un fork para que el
código del programa pasado por parámetro se ejecute en otro proceso y no sustituya la imagen del
proceso padre.

Sin embargo si usamosk execvp(3) se sustituye la imagen del proceso actual y no se crea ningún hijo por lo que todo el código después de la llamada a la función no se ejecuta (salvo que haya un error en la llamada)  


*/
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

	if(argc == 1){
	
		printf("Usage: ./ejercicio7_1.c <comando entre comillas>\n");
		return -1;
	}

	system(argv[1]);

	printf("El comando terminó de ejecutarse\n\n");
	return 0;
}
