#ifndef WEBSERV_CGI_HPP
#define WEBSERV_CGI_HPP

#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

std::string execution_cgi(char **);

#endif // WEBSERV_CGI_HPP
