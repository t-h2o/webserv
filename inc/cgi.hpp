#ifndef WEBSERV_CGI_HPP
#define WEBSERV_CGI_HPP

#include <map>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 4092

void print_container_map(std::map<std::string, std::string> myMap);

class CGI
{
  private:
	std::map<std::string, std::string> _env;
	std::vector<char *>				   _args;
	std::string						   _output_cgi;
	int								   _pipefd[2];
	char							   _read_buffer[BUFFER_SIZE];

  public:
	CGI(void);
	CGI(const std::string &bin, const std::string &file, const std::string &query);

	std::string execution_cgi(char *args);
	std::string parent_process(pid_t &pid);
	void		child_process(char **);
	void		set_env(char *args);
	~CGI(void);
};

#endif // WEBSERV_CGI_HPP
