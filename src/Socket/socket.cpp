#include "socket.hpp"

Socket::Socket(int domain, int port, int type, int protocol, u_long interface)
{
	_address.sin_family = domain;
	_address.sin_port = htons(port);
	_address.sin_addr.s_addr = htonl(interface);

	create_socket(domain, type, protocol);
	set_socket_non_blocking();
	binding_socket();
	start_listening();
}

void
Socket::create_socket(int domain, int type, int protocol)
{
	_sock_id = socket(domain, type, protocol);
	test_socket(_sock_id, "create_socket() Fail!");
}

void
Socket::binding_socket()
{
	_connection = bind(_sock_id, (struct sockaddr *)&_address, sizeof(_address));
	test_socket(_connection, "binding_socket() Fail!");
}

void
Socket::start_listening()
{
	int res;
	res = listen(_sock_id, 10);
	test_socket(res, "start_listening() Fail!");
}

void
Socket::test_socket(int item_to_test, const char *msg)
{
	if (item_to_test < 0)
	{
		std::cerr << msg << std::endl;
		close(_sock_id);
		throw Socket::SocketException();
	}
}

int
Socket::get_sock_id() const
{
	return _sock_id;
}

unsigned short int Socket::get_port() const
{
	return ntohs(_address.sin_port);
}

void Socket::set_socket_non_blocking()
{
	int ret;
	int val = 1;
	ret = setsockopt(_sock_id, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	test_socket(ret, "setsockopt() Fail!");

	// Following code only working after select() is implemented
	// ret = fcntl(_sock_id, F_SETFL, O_NONBLOCK);
	// test_socket(ret, "fcnt() Fail!");
}

const char *Socket::SocketException::what() const throw()
{
	return "Exception: Socket set up failed.";
}
