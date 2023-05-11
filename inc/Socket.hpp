#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "Request.hpp"
#include "Response.hpp"
#include <climits>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define LISTEN_BACKLOG 10
#define MAXLINE 4096

#define LOG_SOCKET false

class Socket
{
  private:
	const json::Value &_server_config;
	http::Request	   _request;
	http::Response	   _response;
	std::string		   _header_str;
	std::string		   _body_str;
	int				   _connection_fd;
	int				   _socket_id;
	struct sockaddr_in _address;
	void			   create_socket(int domain, int type, int protocol);
	void			   binding_socket();
	void			   start_listening();
	void			   test_socket(int item_to_test, const char *);
	void			   set_socket_non_blocking();
	void			   multipart_handler();
	void			   delete_handler();
	void			   clean_request();
	void			   send_response();
	std::string		   get_file_full_name();
	void			   create_new_file();
	std::string		   clean_end_of_file(std::string const &str_to_clean);
	void			   check_content_lenght_authorized();
	std::string		   my_replace(std::string str, std::string find, std::string replace);

  public:
	Socket(int domain, unsigned short port, int type, int protocol, const json::Value &);
	int socket_recv();
	int socket_accept();
	int get_socket_id() const;
};

#endif
