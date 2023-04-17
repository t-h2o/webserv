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

// return -1 =>
// FD_CLR(socket, &_fd_set);
// FD_CLR(socket, &reading_set);
// _sockets.erase(socket);
// it = _sockets.begin();
// return 0 =>
// push socket_fd to readytowrite

int
Socket::socket_recv()
{
	const int MAXLINE = 4096;
	char	  buffer[MAXLINE] = { 0 };
	int		  byte_read;
	int		  send_ret = 0;

	byte_read = recv(_connection_fd, buffer, MAXLINE - 1, 0);
	if (byte_read == 0 || byte_read == -1)
	{
		close(_connection_fd);
		if (byte_read == 0)
			std::cout << "\rConnection was closed by client.\n" << std::endl;
		else
			std::cout << "\rRead error, closing connection.\n" << std::endl;
		return (-1);
	}
	request_str += buffer;
	request.parse_buffer(request_str);
	std::cout << request << std::endl;
	if (request_str.find("Transfer-Encoding:chunked") != std::string::npos)
	{
		// process chunk
		while (byte_read > 0)
		{
			std::cout << "RECV SIZE: " << byte_read << std::endl;
			std::memset(buffer, 0, MAXLINE);
			byte_read = 0;
			byte_read = recv(_connection_fd, buffer, MAXLINE - 1, 0);
		}
	}
	// return 1;

	request.parse_buffer(request_str);
	request_str = "";
	response.load_http_request(request);
	std::string response(this->response.get_http_response());
	send_ret = send(_connection_fd, response.c_str(), response.length(), 0);
	if (send_ret < static_cast<int>(response.length()))
	{
		std::cout << "send_ret : " << send_ret << std::endl;
		send_ret = send(_connection_fd, response.c_str(), response.length(), 0);
	}
	close(_connection_fd);
	return 0;
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
