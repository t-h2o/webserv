#include "arguments.hpp"
#include "webserver.hpp"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void
pipe_two_proccess(void)
{
	int	  pipefd[2];
	char  array[6];
	pid_t pid;

	pipe(pipefd);

	pid = fork();

	if (pid == 0) // child
	{
		printf("child: fd[0] = %d\n", pipefd[0]);
		printf("child: fd[1] = %d\n", pipefd[1]);
	}
	else // parent
	{
		printf("parent fd[0] = %d\n", pipefd[0]);
		printf("parent fd[1] = %d\n", pipefd[1]);
	}

	return;

	write(pipefd[1], "hello", 5);
	write(pipefd[1], "world", 5);

	read(pipefd[0], array, 5);
	printf("%d %d array = %s\n", pipefd[0], pipefd[1], array);

	read(pipefd[0], array, 5);
	printf("%d %d array = %s\n", pipefd[0], pipefd[1], array);
}

void
pipe_one(void)
{
	int	 pipefd[2];
	char array[6];

	pipe(pipefd);

	write(pipefd[1], "hello", 5);
	write(pipefd[1], "world", 5);

	read(pipefd[0], array, 5);
	printf("%d %d array = %s\n", pipefd[0], pipefd[1], array);

	read(pipefd[0], array, 5);
	printf("%d %d array = %s\n", pipefd[0], pipefd[1], array);
}

void
one_fd(void)
{
	int	 fd;
	char array[6];

	/* write into fd */

	fd = open("./newfile", O_WRONLY | O_CREAT | O_TRUNC);

	if (fd == -1)
	{
		printf("error: open()\n");
		return;
	}

	printf("fd is %d\n", fd);

	write(fd, "hello", 5);

	close(fd);

	/* read from fd */

	fd = open("./newfile", O_RDONLY);

	read(fd, array, 5);

	printf("%d array = %s\n", fd, array);

	close(fd);
}

int
main(int argc, char **argv, char **envp)
{
	//	pipe_two_proccess();

	if (check_argc_number(argc))
		return 1;

	return webserver(argv[1], envp);
}
