#include "../../inc/cgi.hpp"

/* pseudo code CGI
 * variables list:
 * - path of the cgi binary file
 * - path of the php file
 * execution
 * see: https://t-h2o.github.io/microshell/#_execution
 * 1. execve(path, arguments, envp)
 * 2. GOAL: put the output into a std::string
 * difficulty:
 * - redirection pipe -> std::string
 * - whats are the arguments to put into execve()
 */

int
execution_cgi(char **envp)
{
	char	args[6];
	int	 	pipefd[2];
	(void) envp;

	if (pipe(pipefd) == -1)
	{
		std::cerr << "error pipe" << std::endl;
		return (1);
	}
	pid_t pid = fork();

	if (pid == -1)
	{
		std::cerr << "error fork" << std::endl;
		return (1);
	}
	else if (pid == 0)
	{
		// child process
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		write(pipefd[1], "hello", 5);
		close(pipefd[1]);
	}

	else
	{
		// parent process
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		read(pipefd[0], args, 5);
		printf("array = %s\n", args);
		close(pipefd[0]);
	}

return (0);
}
