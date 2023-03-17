#ifndef SOCKET_HPP
#define SOCKET_HPP
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

class Socket
{
  private:
	int				   _sock_id;
	int				   _connection;
	struct sockaddr_in _address;
	void create_socket(int domain, int type, int protocol);
	void binding_socket();
	void start_listening();
	void test_socket(int item_to_test, const char *);
	void set_socket_non_blocking();

  public:
	Socket(int domain, int port, int type, int protocol, u_long interface);
	int	 get_sock_id() const;
	unsigned short int get_port() const;

	class SocketException : public std::exception
	{
		public:
			const char *what() const throw();
	};
};

#endif
