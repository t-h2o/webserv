#include "../../inc/cgi.hpp"
#include "../../inc/std98.hpp"
#include "../../inc/utility.hpp"
#include "cgi.hpp"
#include "stdio.h"

#define BUFFER_SIZE 4092

CGI::CGI(void) : _pipefd(), _read_buffer() {}

CGI::CGI(const CGI &src) : _pipefd(), _read_buffer() { *this = src; }

CGI::CGI(const std::string &bin, const std::string &file, const std::string &query)
	: _pipefd(), _read_buffer()
{
	_args.push_back(const_cast<char *>(bin.c_str()));
	_args.push_back(const_cast<char *>(file.c_str()));
	if (!query.empty())
		_args.push_back(const_cast<char *>(query.c_str()));
	_args.push_back(NULL);
}

/*
 * Environment variables in PHP-CGI serve as a way to provide configuration values, system
 * information, and sensitive data to PHP scripts during their execution, allowing for better separation of
 * concerns, improved security, and easier management of dependencies and configurations.
 */
void
CGI::set_env(char *args)
{
	//	// Définit la route par laquelle tous les utilisateurs seront authentifiés (dans les applications
	// prises
	//	// en charge).
	//	_env["AUTH_TYPE"] = "null";
	//	// Donne le nombre de bytes transmis par le client.
	//	_env["CONTENT_LENGTH"] = std98::to_string(1000);
	//	// Donne le type de donnée transmise par le client si l'attribut METHOD a pour valeur POST.
	//	_env["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
	//	// Donne la version du CGI utilisé.
	//	_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	//	// Donne l'extra path information utilisée.
	//	_env["PATH_INFO"] = "/foo/bar";
	//	// Donne une traduction d'un chemin virtuel passé dans l'extra path information.
	//	_env["PATH_TRANSLATED"] = args;
	//	// Donne les informations passées par un marqueur <FORM METHOD=GET>
	//	_env["QUERY_STRING"] = "foo=bar&baz=qux";
	//	// Donne la valeur de l'attribut METHOD du marqueur FORM utilisé lors de la requête CGI. En gros le
	// type
	//	// de requete http
	//	_env["REQUEST_METHOD"] = "GET";
	//	// Donne le chemin virtuel du script utilisé. Le nom du script.
	//	_env["SCRIPT_NAME"] = args;
	//	// Donne l'IP ou la DNS du serveur.
	//	_env["SERVER_NAME"] = "null";
	//	// Donne le nom et la version du protocole utilisé par le serveur et le client.
	//	// Cette variable contient généralement une chaîne de texte telle que "HTTP/1.1" ou "HTTP/2.0",
	//	// qui indique la version du protocole utilisée.
	//	_env["SERVER_PROTOCOL"] = "null";
	//	// Donne le nom et la version du serveur Web utilisé.
	//	_env["SERVER_SOFTWARE"] = "null";
	//	// Indique qu'une requête été redirigée en interne, elle est définie pour la gestion des erreurs.
	//	_env["REDIRECT_STATUS"] = "CGI";
	_env["SCRIPT_FILENAME"] = args;
	_env["REQUEST_METHOD"] = "GET";
	_env["QUERY_STRING"] = "";	 // Set this to the query string if there is one
	_env["CONTENT_TYPE"] = "";	 // Set this to the content type if needed
	_env["CONTENT_LENGTH"] = ""; // Set this to the content length if needed
	_env["REDIRECT_STATUS"] = "200";
}

std::string
CGI::parent_process(pid_t &pid)
{
	int ret;
	close(_pipefd[1]);
	if (waitpid(pid, &ret, 0) == -1)
	{
		std::cout << ret << std::endl;
		throw(std::exception());
	}
	ssize_t bytes_read;
	do
	{
		// Initialize bytes_read with the return value from read, for error checking.
		bytes_read = read(_pipefd[0], _read_buffer, BUFFER_SIZE);
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
	} while (bytes_read == BUFFER_SIZE);
	// Close the process.
	close(_pipefd[0]);
	return (_output_cgi);
}

void
CGI::child_process(char **env)
{
	close(_pipefd[0]);
	// Replace the old FD
	if (dup2(_pipefd[1], 1) == -1)
	{
		perror("dup2");
		close(_pipefd[1]);
	}
	close(_pipefd[1]);
	// Execute new process
	if (execve(_args[0], &_args[0], env) == -1)
		perror("execve");
	exit(1);
}

std::string
CGI::execution_cgi(char *args)
{
	char	  **env;
	std::string output;
	// Verify if pipe failed.
	if (pipe(_pipefd) == -1)
	{
		std::cerr << "error pipe" << std::endl;
		exit(1);
	}
	set_env(args);
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

CGI::~CGI(void){};
