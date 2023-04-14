#include "Socket.hpp"

Socket::Socket(int domain, unsigned short port, int type, int protocol)
{
	_address.sin_family = domain;
	_address.sin_port = htons(port);
	_address.sin_addr.s_addr = htonl(INADDR_ANY);

	create_socket(domain, type, protocol);
	set_socket_non_blocking();
	binding_socket();
	start_listening();
	request_str = "";
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
	_connection = bind(_sock_id, reinterpret_cast<struct sockaddr *>(&_address), sizeof(_address));
	test_socket(_connection, "binding_socket() Fail!");
}

void
Socket::start_listening()
{
	int res;
	res = listen(_sock_id, LISTEN_BACKLOG);
	test_socket(res, "start_listening() Fail!");
}

void
Socket::test_socket(int item_to_test, const char *msg)
{
	if (item_to_test < 0)
	{
		close(_sock_id);
		throw std::runtime_error(msg);
	}
}

int
Socket::get_sock_id() const
{
	return _sock_id;
}

unsigned short
Socket::get_port() const
{
	return ntohs(_address.sin_port);
}

void
Socket::set_socket_non_blocking()
{
	int ret;
	int val = 1;
	ret = setsockopt(_sock_id, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	test_socket(ret, "setsockopt() Fail!");

	// Following code only working after select() is implemented
	// ret = fcntl(_sock_id, F_SETFL, O_NONBLOCK);
	// test_socket(ret, "fcnt() Fail!");
}

void
Socket::socket_recv()
{
	const int MAXLINE = 4096;
	char	  buffer[MAXLINE] = { 0 };
	int		  byte_read;

	byte_read = recv(_connection_fd, buffer, MAXLINE - 1, 0);
	while (byte_read > 0)
	{
		std::cout << "RECV SIZE: " << byte_read << std::endl;
		request_str += buffer;
		std::memset(buffer, 0, MAXLINE);
		if (byte_read == MAXLINE - 1)
			byte_read = recv(_connection_fd, buffer, MAXLINE - 1, 0);
		else
			byte_read = 0;
	}
	request.parse_buffer(request_str);
	request_str = "";
}

void
Socket::socket_accept()
{
	_connection_fd = accept(get_sock_id(), NULL, NULL);
	if (_connection_fd < 0)
	{
		std::cout << "connection_fd: " << _connection_fd << " Failed!" << std::endl;
		exit(EXIT_FAILURE);
	}
}