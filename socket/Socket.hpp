#ifndef SOCKET_HPP
#define SOCKET_HPP
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

class Socket
{
private:
	int _sock_id;
	int _connection;
	struct sockaddr_in _address;


public:
	Socket(int domain, int port, int type, int protocol, u_long interface);
	void createSocket(int domain, int type, int protocol);
	void establishConnection();
	void startListening();
	void test_socket(int item_to_test);
	int get_sock_id() const;

};

#endif
