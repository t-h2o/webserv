#include "cgi.hpp"

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

	// Verify if pipe failed.
	if (pipe(pipefd) == -1)
	{
		std::cerr << "error pipe" << std::endl;
		return (1);
	}

	pid_t pid = fork();

	// Verify if fork failed
	if (pid == -1)
	{
		std::cerr << "error fork" << std::endl;
		return (1);
	}
	else if (pid == 0)
	{
		// Child process
		// Path to the cgi
		arguments[0] = (char *)"/Users/kdi-noce/goinfre/bin/php-cgi";
		// The php file who contain phpinfo(), a big configuration function.
		arguments[1] = (char *)"test.php";
		arguments[2] = NULL;

		close(pipefd[0]);
		// Replace the old FD
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		// Execute new process
		execve(arguments[0], arguments, envp);
		perror("execve");
		exit(1);
	}

	else
	{
		// parent process
		close(pipefd[1]);

		while (true)
		{
			// Initialize bytes_read with the return value from read, for error checking.
			ssize_t bytes_read = read(pipefd[0], read_buffer, BUFFER_SIZE);
			// Condition if read fail
			if (bytes_read == -1)
			{
				/* EINTR error code if a signal occurred while the system call was in progress. No error
				 * actually occurred, it's just reported that way because the system isn't able to resume the
				 * system call automatically. This coding pattern simply retries the system call when this
				 * happens, to ignore the interrupt.
				 * */
				if (errno == EINTR)
					continue;
				else
				{
					perror("read");
					close(pipefd[0]);
					return (1);
				}
			}
			// End of file
			else if (!bytes_read)
				break;
			// std::string output_cgi concatenation with append
			else
				output_cgi.append(read_buffer, bytes_read);
			// Fill read_buffer with 0
			std::memset(read_buffer, 0, BUFFER_SIZE);
		}
		std::cout << "read: " << output_cgi << std::endl;
		// Close the process.
		close(pipefd[0]);
	}
	return (0);
}
