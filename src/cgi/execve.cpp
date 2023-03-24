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
	char	array[11];
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
		std::cout << "child" << std::endl;
		std::cout << pipefd[1] << std::endl;
		std::ofstream infile("test.txt");

		infile << "hello world";

		close(pipefd[0]);
		infile.close();
		close(pipefd[1]);
	}

	else
	{
		// parent process
		std::cout << "parent" << std::endl;
		std::cout << pipefd[0] << std::endl;
		close(pipefd[1]);
		int nbytes = read(pipefd[0], array, sizeof(array));
		array[nbytes] = '\0';
		std::cout << array;

		close(pipefd[0]);

		std::ifstream outfile("test.txt");
		std::string line;
		while (std::getline(outfile, line))
			std::cout << "parent process readL: " << line << std::endl;
		outfile.close();
	}

return (0);
}
