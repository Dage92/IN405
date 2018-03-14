#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

//pid_t wait(int *status);

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
			"Mon PID est %d et celui de mon père est %d.\n", (int) getpid(), (int) getppid());
}

void father_process(int child_pid)
{
	printf(	"Hello World!\n"
			"Mon PID est %d et celui de mon fils est %d.\n", (int) getpid(), (int) child_pid);
	if (wait(NULL) == -1)
	{
		perror("wait :");
		exit(EXIT_FAILURE);
	}
}

int main(void)
{
	pid_t pids[10];
	int i;
	int n = 10;
	
	for (i = 0; i<n; i++)
	{
		if ((pids[i] = fork()) < 0)
		{
			perror("fork");
			abort();
		}
		else if (pids[i] == 0)
		{
			DoWorkInChild();
			exit(0);
		}
	}
	
	int status;
	pid_t pid;
	while (n > 0)
	{
		pid = wait(&status);
		printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
		--n;
	}
	/*pid_t pid = create_process();
	
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
	return EXIT_SUCCESS;*/
}
