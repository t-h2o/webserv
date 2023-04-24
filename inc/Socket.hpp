#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "Request.hpp"
#include "Response.hpp"
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

class Socket
{
  private:
	int				   _sock_id;
	int				   _connection;
	struct sockaddr_in _address;
	void			   create_socket(int domain, int type, int protocol);
	void			   binding_socket();
	void			   start_listening();
	void			   test_socket(int item_to_test, const char *);
	void			   set_socket_non_blocking();

  public:
	int			   _connection_fd;
	http::Request  request;
	http::Response response;
	std::string	   header_str;
	std::string	   body_str;
	std::string	   dir_path;
	Socket(int domain, unsigned short port, int type, int protocol, std::string path);
	int			   socket_recv();
	void		   socket_accept();
	int			   get_sock_id() const;
	unsigned short get_port() const;
	std::string	   get_file_name(std::string);
	void		   create_new_file(std::string);
	std::string	   clean_end_of_file(std::string str_to_clean);
	std::string	   get_dir_path() const;
	void		   multipart_handler(int);
	void		   delete_handler();
	void		   clean_request();
	void		   send_response();
};

#endif
