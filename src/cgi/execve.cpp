#include "../../inc/cgi.hpp"
#include "../../inc/utility.hpp"
#include "cgi.hpp"

#define BUFFER_SIZE 4092

CGI::CGI() {}

CGI::CGI(const CGI &src) { *this = src; }

CGI::CGI(std::string bin, std::string file, std::string query)
{
	_args.push_back((char *)bin.c_str());
	_args.push_back((char *)file.c_str());
	if (!query.empty())
		_args.push_back((char *)query.c_str());
	_args.push_back(NULL);
}
// CGI CGI::operator=(const CGI &src) {
//	*this = src;
//	return (*this);
// }
void
CGI::set_env()
{
	// Définit la route par laquelle tous les utilisateurs seront authentifiés (dans les applications prises
	// en charge).
	_env["AUTH_TYPE"] = "null";
	// Donne le nombre de bytes transmis par le client.
	_env["CONTENT_LENGTH"] = std::to_string(19);
	// Donne le type de donnée transmise par le client si l'attribut METHOD a pour valeur POST.
	_env["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
	// Donne la version du CGI utilisé.
	_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	// Donne l'extra path information utilisée.
	_env["PATH_INFO"] = "/foo/bar";
	// Donne une traduction d'un chemin virtuel passé dans l'extra path information.
	_env["PATH_TRANSLATED"] = "/Users/kdi-noce/Documents/cursus42/webserv/test.php";
	// Donne les informations passées par un marqueur <FORM METHOD=GET>
	_env["QUERY_STRING"] = "foo=bar&baz=qux";
	// Donne la valeur de l'attribut METHOD du marqueur FORM utilisé lors de la requête CGI. En gros le type
	// de requete http
	_env["REQUEST_METHOD"] = "POST";
}

// void
// CGI::s_env(void)
//{
//	_request = std::getenv("REQUEST_METHOD");
//	_script = std::getenv("SCRIPT_NAME");
//	_server_N = std::getenv("SERVER_NAME");
//	_server_Port = std::getenv("SERVER_NAME");
//	_server_Protocol = std::getenv("SERVER_PROTOCOL");
//	_server_S = std::getenv("SERVER_SOFTWARE");
// }

std::string
CGI::parent_process(pid_t pid)
{
	close(_pipefd[1]);
	waitpid(pid, 0, 0);
	while (true)
	{
		// Initialize bytes_read with the return value from read, for error checking.
		ssize_t bytes_read = read(_pipefd[0], _read_buffer, BUFFER_SIZE);
		// Condition if read fail
		if (bytes_read == -1)
		{
			perror("read");
			close(_pipefd[0]);
			exit(1);
		}
		// End of file
		else if (!bytes_read)
			break;
		// std::string output_cgi concatenation with append
		else
			_output_cgi.append(_read_buffer, bytes_read);
		// Fill _read_buffer with 0
		std::memset(_read_buffer, 0, BUFFER_SIZE);
	}
	// Close the process.
	close(_pipefd[0]);
	return (_output_cgi);
}

void
CGI::child_process(char **env)
{
	close(_pipefd[0]);
	// Replace the old FD
	dup2(_pipefd[1], STDOUT_FILENO);
	close(_pipefd[1]);

	// Execute new process
	execve(_args[0], &_args[0], env);
	perror("execve");
	exit(1);
}

std::string
CGI::execution_cgi(void)
{
	char	  **env;
	std::string output;
	// Verify if pipe failed.
	if (pipe(_pipefd) == -1)
	{
		std::cerr << "error pipe" << std::endl;
		exit(1);
	}
	set_env();
	env = utils::cMap_to_cChar(_env);
	pid_t pid = fork();
	// Verify if fork failed
	if (pid == -1)
	{
		std::cerr << "error fork" << std::endl;
		exit(1);
	}
	else if (pid == 0)
		child_process(env);
	else
		output = parent_process(pid);
	return (output);
}

CGI::~CGI(void) {}
