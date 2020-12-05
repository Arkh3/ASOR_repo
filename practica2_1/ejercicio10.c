#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pwd.h>


int main(){
	
	uid_t id = getuid();
	
	struct passwd pswd;
	
	pswd = *getpwuid(id);
	
	printf("UID real del usuario: %d\nUID efectivo del usuario: %d\nNombre del usuario: %s\nDescripcion del usuario: %s\nDirectorio Home: %s\n", id, geteuid(), pswd.pw_name, pswd.pw_gecos, pswd.pw_dir);
	return 0;
} 
