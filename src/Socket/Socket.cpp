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
	header_str = "";
	body_str = "";
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
	std::string buffer_str = std::string(buffer);
	header_str += buffer_str.substr(0, buffer_str.find("\r\n\r\n"));
	if (buffer_str.find("\r\n\r\n") + 4 != buffer_str.size())
		body_str += buffer_str.substr(buffer_str.find("\r\n\r\n"));
	request.parse_buffer(header_str);
	if (request._request_map["Content-Type"] == "multipart/form-data")
	{
		while (byte_read == MAXLINE - 1)
		{
			std::memset(buffer, 0, MAXLINE);
			byte_read = read(_connection_fd, buffer, MAXLINE - 1);
			body_str += buffer;
		}
		std::memset(buffer, 0, MAXLINE);
		create_new_file(body_str);
		// std::cout << body_str << std::endl;
	}

	// std::cout << request << std::endl;
	response.load_http_request(request);
	header_str = "";
	body_str = "";
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

std::string
Socket::get_file_name(std::string raw_body)
{
	std::string start_looking = raw_body.substr(raw_body.find("filename="));
	start_looking = start_looking.substr(start_looking.find_first_of('"'), start_looking.find("\n"));
	size_t position_quote_start(start_looking.find_first_of('"') + 1);
	size_t length(start_looking.find_first_of('"', +1) - position_quote_start);
	return start_looking.substr(position_quote_start, length);
}

void
Socket::create_new_file(std::string raw_body)
{
	size_t		delimiter = raw_body.find("Content-Type");
	std::string file_name = get_file_name(raw_body.substr(0, delimiter));
	std::string file_part = request.trim(raw_body.substr(raw_body.find_first_of("\r\n\r\n", +delimiter)));
	size_t		end = file_part.find(request._request_map["boundary"]);
	std::string half_clean_file = file_part.substr(0, end);
	std::string fullpath = "test/website/uploads/" + file_name;
	std::string clean_file = clean_end_of_file(half_clean_file);
	// std::cout << raw_body.substr(0, 1000) << std::endl;
	std::ofstream ofs(fullpath, std::ios_base::out | std::ios_base::binary);
	ofs << clean_file;
	ofs.close();
}

std::string
Socket::clean_end_of_file(std::string str_to_clean)
{
	int index = str_to_clean.size() - 1;
	while (str_to_clean[index] == '-' || str_to_clean[index] == '\n')
		--index;
	return str_to_clean.substr(0, index);
}