#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

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
	printf(	"Hello World!\n"
			"Mon PID est %ld et celui de mon père est %ld.\n", (long) getpid(), (long) getppid());
}

void father_process(int child_pid)
{
	
	printf(	"Hello World!\n"
			"Mon PID est %ld et celui de mon fils est %ld.\n", (long) getpid(), (long) child_pid);
}

int main(void)
{
	srand(pid);
	pid_t pid = create_process();
	
	
	int r = rand() %50 + 1;
	
	switch (pid)
	{
		case -1:
				perror("fork");
				return EXIT_FAILURE;
				break;
		case 0:
				child_process();
				printf ("Le nombre que j'ai choisit est %d.\n", r);
				break;
		default:
				father_process(pid);
				printf ("Le nombre que mon fils à choisit est %d.\n", r);
				break;
	}
	return EXIT_SUCCESS;
}
