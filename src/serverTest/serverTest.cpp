#include "serverTest.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Socket.hpp"
#include "Value.hpp"
#include <cstring>
#include <vector>

void
serverTest(json::t_object *config)
{
	/*
	 *  sock @params:
	 *	AF_INET for IPv4,
	 *	Port number,
	 *	SOCK_STREAM bidirectional byte-stream socket,
	 *	AF_INET + SOCK_STREAM always protocol = 0,
	 *	address for this socket, let the OS choose = INADDR_ANY
	 */

	json::Value val(config);
	const int	MAXLINE = 1000;
	std::cout << "HERE " << std::endl;
	unsigned short			 port = val.get("port").get<double>();
	Socket					 sock(AF_INET, port, SOCK_STREAM, 0);
	int						 connection_fd;
	// char					 buffer[MAXLINE] = { 0 };
	// int						 recv_return;
	http::Request			 req;
	http::Response			 res;
	std::vector<std::string> header;
	int						 send_ret = 0;

	std::cout << "port : " << port << std::endl;

	while (1)
	{
		std::cout << "++++++ Waiting for new connection ++++++" << std::endl;
		std::cout << "SOCK Port: " << sock.get_port() << std::endl;

		sock.socket_accept();
		sock.socket_recv();

		std::cout << "CONNECTION CLOSED" << std::endl;
	}
}
