#ifndef WEBSERV_CGI_HPP
#define WEBSERV_CGI_HPP
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <cassert>

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
	CGI(CGI const &src);
	//	CGI		operator=(CGI const& src);

	std::string get_env(const std::string& key) const;
	std::string	execution_cgi(char *args);
	std::string parent_process(pid_t& pid);
	void		child_process(char **);
	void		set_env(char *args);
//	void		prepare_env(const std::string &bin, const std::string &file, const std::string &query);
	~CGI(void);
};

#endif // WEBSERV_CGI_HPP
