#ifndef WEBSERV_CGI_HPP
#define WEBSERV_CGI_HPP
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#define BUFFER_SIZE 4092

void print_container_map(std::map<std::string, std::string> myMap);

class CGI
{
  private:
	std::map<std::string, std::string>	_env;
	std::vector<char *>					_args;
	std::string							_output_cgi;
	int									_pipefd[2];
	char								_read_buffer[BUFFER_SIZE];

  public:
	CGI(void);
	CGI(CGI const &src);
	CGI(std::string bin, std::string file, std::string query);
	//	CGI		operator=(CGI const& src);

	std::string execution_cgi(void);
	std::string parent_process(pid_t pid);
	void		child_process(char **);
	void		set_env(void);
	void		check_env(void);

	~CGI(void);
};
#endif // WEBSERV_CGI_HPP
