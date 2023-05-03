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

#define LOG_SOCKET false

class Socket
{
  private:
	http::Request	   _request;
	http::Response	   _response;
	std::string		   _header_str;
	std::string		   _body_str;
	std::string		   _dir_path;
	int				   _connection_fd;
	int				   _sock_id;
	int				   _connection;
	unsigned long	   _max_content_length;
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
	const std::string &get_dir_path() const;
	void			   check_content_lenght_authorized();

  public:
	Socket(int domain, unsigned short port, int type, int protocol, std::string path,
		   unsigned long max_length);
	int	 socket_recv();
	void socket_accept();
	int	 get_sock_id() const;
};

#endif
