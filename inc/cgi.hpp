//
// Created by Kevin Di nocera on 3/16/23.
//

#ifndef WEBSERV_CGI_HPP
#define WEBSERV_CGI_HPP
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int execution_cgi(char **);
#endif // WEBSERV_CGI_HPP
