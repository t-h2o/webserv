#include "../../inc/cgi.hpp"
#define BUFFER_SIZE 4092

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
	int			pipefd[2];
	char	   *arguments[3];
	std::string output_cgi;
	char		read_buffer[BUFFER_SIZE];

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
		arguments[0] = (char *)"/Users/kdi-noce/goinfre/bin/php-cgi";
		arguments[1] = (char *)"test.php";
		arguments[2] = NULL;

		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		execve(arguments[0], arguments, envp);
		perror("execve");
	}

	else
	{
		// parent process
		close(pipefd[1]);

		while (true)
		{
			ssize_t bytes_read = read(pipefd[0], read_buffer, BUFFER_SIZE);
			if (bytes_read == -1)
			{
				if (errno == EINTR)
					continue;
				else
				{
					perror("read");
					close(pipefd[0]);
					return (1);
				}
			}
			else if (!bytes_read)
				break;
			else
				output_cgi.append(read_buffer, bytes_read);
			std::memset(read_buffer, 0, BUFFER_SIZE);
		}
		output_cgi += read_buffer;
		std::cout << "read: " << output_cgi << std::endl;
		close(pipefd[0]);
	}
	return (0);
}
