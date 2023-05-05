#include "../../inc/cgi.hpp"
#include "../../inc/std98.hpp"
#include "../../inc/utility.hpp"
#include "cgi.hpp"
#include "stdio.h"

#define BUFFER_SIZE 4092

CGI::CGI(void) {}

CGI::CGI(const std::string &bin, const std::string &file, const std::string &query)
{
	char *b;
	char *f;
	char *q;

	b = new char[bin.size() + 1];
	f = new char[file.size() + 1];
	std::memcpy(b, bin.c_str(), bin.size() + 1);
	std::memcpy(f, file.c_str(), file.size() + 1);
	_args.push_back(b);
	_args.push_back(f);
	if (!query.empty())
	{
		q = new char[query.size() + 1];
		std::memcpy(q, query.c_str(), query.size() + 1);
		_args.push_back(q);
	}
	_args.push_back(NULL);
}

/*
 * Environment variables in PHP-CGI serve as a way to provide configuration values, system
 * information, and sensitive data to PHP scripts during their execution, allowing for better separation of
 * concerns, improved security, and easier management of dependencies and configurations.
 */
void
CGI::set_env(const std::map<std::string, std::string>& map, std::string args)
{
	//		// Définit la route par laquelle tous les utilisateurs seront authentifiés (dans les applications
	//	 // prises
	//		// en charge).
	//		_env["AUTH_TYPE"] = "";
	//		// Donne le nombre d'octets transmis par le client.
	//		_env["CONTENT_LENGTH"] = "1000";
	//		// Donne le type de donnée transmise par le client si l'attribut METHOD a pour valeur POST.
	//		_env["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
	//		// Donne la version du CGI utilisé.
	//		_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	//		// Donne l'extra path information utilisée.
	//		// identifies the resource or sub-resource to be returned by the script, and is derived from the
	//		// portion of the URI path hierarchy following the part that identifies the script itself
	//	 	// http://some.machine/cgi-bin/display.pl/cgi/cgi_doc.txt => /cgi/cgi_doc.txt
	//		_env["PATH_INFO"] = "/foo/bar";
	//		// Donne une traduction d'un chemin virtuel passé dans l'extra path information.
	//		_env["PATH_TRANSLATED"] = args;
	//		// Donne les informations passées par un marqueur <FORM METHOD=GET>
	//		_env["QUERY_STRING"] = "foo=bar&baz=qux";
	//		// Donne la valeur de l'attribut METHOD du marqueur FORM utilisé lors de la requête CGI. En gros
	// le
	//	 // type
	//		// de requete http
	//		_env["REQUEST_METHOD"] = "GET";
	//		// Donne le chemin virtuel du script utilisé. Le nom du script.
	//		_env["SCRIPT_NAME"] = args;
	//		// Donne l'IP ou le DNS du serveur.
	//		_env["SERVER_NAME"] = "";
	//		// Donne le nom et la version du protocole utilisé par le serveur et le client.
	//		// Cette variable contient généralement une chaîne de texte telle que "HTTP/1.1" ou "HTTP/2.0",
	//		// qui indique la version du protocole utilisée.
	//		_env["SERVER_PROTOCOL"] = "";
	//		// Donne le nom et la version du serveur Web utilisé.
	//		_env["SERVER_SOFTWARE"] = "";
	//		// Indique qu'une requête été redirigée en interne, elle est définie pour la gestion des erreurs.
	//		_env["REDIRECT_STATUS"] = "CGI";


	_env["AUTH_TYPE"] = "";

	struct stat sa = {};
	_env["SCRIPT_NAME"] = "";
	if (stat("/Users/kdi-noce/goinfre/php/php-8.2.5/sapi/cgi/php-cgi", &sa) == 0)
		_env["SCRIPT_FILENAME"] = "/Users/kdi-noce/goinfre/php/php-8.2.5/sapi/cgi/php-cgi";

	std::map<std::string, std::string>::const_iterator it = map.find("Path");
	_env["SCRIPT_FILENAME"] = "";
	if (it != map.end() && !it->second.empty())
	{
		struct stat sb = {};
		if (stat(args.c_str(), &sb) == 0)
			_env["SCRIPT_FILENAME"] = args;
	}

	it = map.find("Content-Type");
	_env["CONTENT_TYPE"] = "";
	if (it != map.end() && !it->second.empty())
		_env["CONTENT_TYPE"] = it->second;

	it = map.find("Content-Length");
	_env["CONTENT_LENGTH"] = "";
	if (it != map.end() && !it->second.empty())
		_env["CONTENT_LENGTH"] = it->second;

	it = map.find("Method");
	_env["REQUEST_METHOD"] = "";
	if (it != map.end() && !it->second.empty())
		_env["REQUEST_METHOD"] = it->second;

	it = map.find("Query");
	_env["QUERY_STRING"] = "";
	if (it != map.end() && !it->second.empty())
		_env["QUERY_STRING"] = it->second;

	it = map.find("Server-Name");
	_env["SERVER_NAME"] = "";
	if (it != map.end() && !it->second.empty())
		_env["SERVER_NAME"] = it->second;

	it = map.find("Server-Test");
	_env["SERVER_PORT"] = "";
	if (it != map.end() && !it->second.empty())
		_env["SERVER_PORT"] = it->second;

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
		// Fill _read_buffer with 0
		std::memset(_read_buffer, 0, BUFFER_SIZE);
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

static void
free_env(char **env)
{
	for (unsigned int index = 0; env[index]; ++index)
	{
		delete[] env[index];
	}
	delete[] env;
}

std::string
CGI::execution_cgi(const std::map<std::string, std::string>& map, std::string args)
{
	char **env;
	// Verify if pipe failed.
	if (pipe(_pipefd) == -1)
	{
		std::cerr << "error pipe" << std::endl;
		exit(1);
	}
	set_env(map, args);
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
		parent_process(pid);
	while (!_args.empty())
	{
		delete[] _args.back();
		_args.pop_back();
	}
	free_env(env);
	return (_output_cgi);
}

CGI::~CGI(void){};
