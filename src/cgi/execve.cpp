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
	int	 	pipefd[2];
	char	*arguments[3];
	(void)	envp;

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
		arguments[0] = (char *) "/Users/kdi-noce/goinfre/bin/php-cgi";
		arguments[1] = (char *) "test.php";
		arguments[2] = NULL;

		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		execvp(arguments[0], arguments);
		perror("execve");
	}

	else
	{
		// parent process
		close(pipefd[1]);

		int fd = open("test.html", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
		{
			perror("open");
			return (1);
		}
		char	buffer[4096];
		ssize_t	nbytes;
		while ((nbytes = read(pipefd[0], buffer, sizeof(buffer))) > 0)
		{
			if (write(fd, buffer, nbytes) != nbytes)
			{
				perror("write");
				return (1);
			}
		}
		close(pipefd[0]);
		if (close(fd) == -1)
		{
			perror("close");
			return (1);
		}
		int status;
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("close");
			return (1);
		}
		if (WIFEXITED(status)) {
			int exit_status = WEXITSTATUS(status);
			if (exit_status != 0) {
				std::cerr << "Command exited with status " << exit_status << std::endl;
				return 1;
			}
		}
		else
		{
			std::cerr << "Command exited abnormally" << std::endl;
			return 1;
		}
//		int nbytes = read(pipefd[0], array, sizeof(array));
//		array[nbytes] = '\0';
//		std::cout << array;


//		std::ifstream outfile("test.txt");
//		std::string line;
//		while (std::getline(outfile, line))
//			std::cout << "parent process readL: " << line << std::endl;
//		outfile.close();
	}

return (0);
}
