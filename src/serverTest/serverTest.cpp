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

		connection_fd = accept(sock.get_sock_id(), NULL, NULL);
		if (connection_fd < 0)
		{
			std::cout << "connection_fd: " << connection_fd << std::endl;
			perror("Accept connection error");
			exit(EXIT_FAILURE);
		}
		sock.socket_recv(connection_fd);
		// recv_return = recv(connection_fd, buffer, MAXLINE - 1, 0);
		// while (recv_return > 0 )
		// {
		// 	std::cout << "RECV SIZE: " << recv_return << std::endl;
		// 	sock._request_str += buffer;
		// 	std::memset(buffer, 0, MAXLINE);
		// 	if (recv_return == MAXLINE -1)
		// 		recv_return = recv(connection_fd, buffer, MAXLINE - 1, 0);
		// 	else
		// 		recv_return = 0;



		// }
		// std::cout << "out of the loop recv..." << std::endl;
		// req.parse_buffer(sock._request_str);
		// sock._request_str = "";
		// if (req.get_method() == "POST")
		// {
		// 	while (recv_return > 0)
		// 	{
		// 		if (buffer[recv_return - 1] == '\n' || recv_return < MAXLINE)
		// 		{
		// 			break;
		// 		}
		// 		std::memset(buffer, 0, MAXLINE);
		// 		recv_return = recv(connection_fd, buffer, MAXLINE - 1, 0);
		// 	}
		// }
		std::cout << "***************** HTTP REQUEST START****************" << std::endl;
		// std::cout << req << std::endl;
		std::cout << "***************** HTTP REQUEST END ****************\n";

		res.load_http_request(sock.request);
		// std::cout << "***************** HTTP REPONSE START****************" << std::endl;
		// std::cout << res << std::endl;
		// std::cout << "***************** HTTP REPONSE END ****************\n" << std::endl;

		std::string response(res.get_http_response());
		send_ret = send(connection_fd, response.c_str(), response.length(), 0);
		if (send_ret < static_cast<int>(response.length()))
		{
			std::cout << "send_ret : " << send_ret << std::endl;
			send_ret = send(connection_fd, response.c_str(), response.length(), 0);
		}
		close(connection_fd);
		std::cout << "CONNECTION CLOSED" << std::endl;
	}
}
