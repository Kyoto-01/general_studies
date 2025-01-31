#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>

#define SCRIPTS_DIR "../scripts/"
#define SCRIPT_NAME "loop.sh"

void check_error(int retcode, char* msg) {

	if (retcode == -1) {
		if (msg != NULL) perror(msg);
		// exit syscall
		exit(errno);
	}
}

void get_time(void) {	
	
	// time syscall
	
	int s;
	
	s = time(NULL);
	check_error(s, "Fail while time.\n");
	printf("=== time ===\n");
	printf("%d seconds\n", s);
	printf("============\n");
}

void get_getcwd(void) {

	// getcwd syscall

	char* s;
	char workdir[255];

	s = getcwd(workdir, sizeof(workdir));
	if (s == NULL)
		check_error(-1, "Fail while getcwd.\n");
	printf("=== getcwd ===\n");
	printf("%s\n", workdir);
	printf("==============\n");
}

void get_chdir(void) {

	// chdir syscall

	int s;

	s = chdir(SCRIPTS_DIR);
	check_error(s, "Fail while chdir.\n");
	printf("=== chdir ===\n");
	printf("%s\n", SCRIPTS_DIR);
	printf("=============\n");	
}	

void get_chmod(int mode) {

	// chmod syscall

	int s;

	s = chmod(SCRIPT_NAME, mode);
	check_error(s, "Fail while chdir.\n");
	printf("=== chmod ===\n");
	system("ls -l");
	printf("=============\n");
}

void get_exec(void) {

	int s;

	// fork syscall
	
	s = fork();
	check_error(s, "Fail while fork.\n");
	if (s == 0) {
		printf("=== fork ===\n");
		system("sleep 2");
		printf("============\n");
	} else {
		// exec syscall
		s = execv(SCRIPT_NAME, NULL);
		check_error(s, "Fail while execv.\n");
	}
}

void get_kill() {

	// kill syscall
	
	int s;

	s = kill(-1, 2);
	check_error(s, "Fail while kill.\n");
	printf("=== kill ===\n");
	printf("%d\n", -1);
	printf("============\n");
}

int main(void) {

	int pid;

	get_time();
	get_getcwd();
	get_chdir();
	get_getcwd();
	get_chmod(0755);
	get_exec();
	get_kill();
	get_chmod(0644);
	get_time();

	return 0;
}
