#include "Socket.hpp"

Socket::Socket(int domain, unsigned short port, int type, int protocol, std::string path)
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
	_dir_path = path;
	response.set_dir_path(_dir_path);
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
	char		buffer[MAXLINE] = { 0 };
	int			byte_read;
	std::string tmp_buffer;

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
	tmp_buffer = std::string(buffer);
	header_str += tmp_buffer.substr(0, tmp_buffer.find("\r\n\r\n"));
	// body_str in vector<unsigned char>
	if (tmp_buffer.find("\r\n\r\n") + 4 != tmp_buffer.size())
	{
		body_str += tmp_buffer.substr(tmp_buffer.find("\r\n\r\n") + 4);
	}
	request.parse_buffer(header_str);
	if (request._request_map["Content-Type"] == "multipart/form-data")
	{
		multipart_handler(byte_read);
		std::memset(buffer, 0, MAXLINE);
	}
	if (request.get_method().compare("DELETE") == 0)
	{
		delete_handler();
	}
	response.load_http_request(request);
	clean_request();
	send_response();
	return 0;
}

void
Socket::multipart_handler(int read_prev)
{
	int	 byte_read = read_prev;
	char buffer[MAXLINE] = { 0 };

	while (byte_read == MAXLINE - 1)
	{
		byte_read = read(_connection_fd, buffer, MAXLINE - 1);
		body_str += buffer;
		std::memset(buffer, 0, MAXLINE);
	}
	create_new_file(body_str);
}

void
Socket::delete_handler()
{
	std::string file_name = request.get_path();

	std::string fullpath = _dir_path + "/uploads" + file_name;
	if (access(fullpath.c_str(), F_OK) != -1)
	{
		request._request_map["FileName"] = "exist";
		int ret = remove(fullpath.c_str());
		if (ret != 0)
			request._request_map["FileName"] = "r_fail";
	}
}

void
Socket::socket_accept()
{
	_connection_fd = accept(get_sock_id(), NULL, NULL);
	if (_connection_fd < 0)
	{
		std::cout << "connection_fd: " << _connection_fd << " Failed!" << std::endl;
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
	std::string fullpath = "test/website/uploads/" + file_name;
	if (access(fullpath.c_str(), F_OK))
	{
		std::string file_part = request.trim(raw_body.substr(raw_body.find_first_of("\r\n\r\n", +delimiter)));
		size_t		end = file_part.find(request._request_map["boundary"]);
		std::string half_clean_file = file_part.substr(0, end);
		std::string clean_file = clean_end_of_file(half_clean_file);
		std::ofstream ofs(fullpath, std::ios_base::out | std::ios_base::binary);
		ofs.write(clean_file.c_str(), clean_file.size() -1);
		ofs.close();
	}
	else
	{
		request._request_map["FileName"] = "exist";
	}
}

std::string
Socket::clean_end_of_file(std::string str_to_clean)
{
	int index = str_to_clean.size() - 1;
	while (str_to_clean[index] == '-' || str_to_clean[index] == '\n')
		--index;
	return str_to_clean.substr(0, index);
}

std::string
Socket::get_dir_path() const
{
	return _dir_path;
}

void
Socket::clean_request()
{
	header_str = "";
	body_str = "";
	request._request_map.clear();
}

void
Socket::send_response()
{
	int			send_ret = 0;
	std::string full_response_str(this->response.get_http_response());
	send_ret = send(_connection_fd, full_response_str.c_str(), full_response_str.length(), 0);
	if (send_ret < static_cast<int>(full_response_str.length()))
	{
		send_ret = send(_connection_fd, full_response_str.c_str(), full_response_str.length(), 0);
	}
	close(_connection_fd);
}
