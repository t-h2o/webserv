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
	json::Value	   val(config);
	unsigned short port = val.get("port").get<double>();
	std::string	   path = val.get("path").get<std::string>();
	Socket sock(AF_INET, port, SOCK_STREAM, 0, path);

	while (1)
	{
		std::cout << "++++++ Waiting for new connection ++++++" << std::endl;

		sock.socket_accept();
		std::cout << "HERE after accept" << std::endl;
		sock.socket_recv();

		std::cout << "CONNECTION CLOSED" << std::endl;
	}
}
