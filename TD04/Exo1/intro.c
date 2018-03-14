#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

/*
pid_t fork(void);			//Prototype de la fonction fork
pid_t getpid(void);			//Retourne le PID du processus appelant
pid_t getppid(void);		//Retourne le PPID du processus appelant
uid_t getuid(void);			//Retourne le UID du processus appelant
gid_t getgid(void);			//Retourne le GID du processus appelant
*/

pid_t create_process(void)
{
	pid_t pid;
	
	do
	{
		pid = fork();
	}
	while ((pid == -1) && (errno == EAGAIN));
	return pid;
}

void child_process(void)
{
	printf(	"Nous sommes dans le fils!\n"
			"Le PID du fils est %d.\n"
			"Le PPID du fils est %d.\n", (int) getpid(), (int) getppid());
}

void father_process(int child_pid)
{
	printf(	"Nous sommes dans le père!\n"
			"Le PID du fils est %d.\n"
			"Le PID du père est %d.\n", (int) child_pid, (int) getpid());
}

int main(void)
{
	pid_t pid = create_process();
	
	switch (pid)
	{
		case -1:
				perror("fork");
				return EXIT_FAILURE;
				break;
		case 0:
				child_process();
				break;
		default:
				father_process(pid);
				break;
	}
	return EXIT_SUCCESS;
}
