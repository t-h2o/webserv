#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "Request.hpp"
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define LISTEN_BACKLOG 10

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
	int			  _connection_fd;
	http::Request request;
	std::string	  request_str;
	Socket(int domain, unsigned short port, int type, int protocol);
	void		   socket_recv();
	void		   socket_accept();
	int			   get_sock_id() const;
	unsigned short get_port() const;
};

#endif
