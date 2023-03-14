#include "httpRequest.hpp"
#include "httpResponse.hpp"
#include "socket.hpp"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

void serverTest()
{
	/*
	 *  sock @params:
	 *	AF_INET for IPv4,
	 *	Port number,
	 *	SOCK_STREAM bidirectional byte-stream socket,
	 *	AF_INET + SOCK_STREAM always protocol = 0,
	 *	address for this socket, let the OS choose = INADDR_ANY
	 */
	Socket					 sock(AF_INET, 8080, SOCK_STREAM, 0, INADDR_ANY);
	int						 connection_fd;
	char					 buffer[MAXLINE] = { 0 };
	int						 recv_return;
	HttpRequest				 requestHandler;
	HttpResponse			 response_handler;
	std::vector<std::string> header;
	int						 send_ret = 0;

	while (1)
	{
		std::cout << "++++++ Waiting for new connection ++++++" << std::endl;
		connection_fd = accept(sock.get_sock_id(), (struct sockaddr *)NULL, NULL);
		if (connection_fd < 0)
		{
			std::cout << "connection_fd: " << connection_fd << std::endl;
			perror("Accept connection error");
			exit(EXIT_FAILURE);
		}
		recv_return = recv(connection_fd, buffer, MAXLINE - 1, 0);
		while (recv_return > 0)
		{
			requestHandler.parseBuffer(buffer);
			if (buffer[recv_return - 1] == '\n' || recv_return < MAXLINE)
			{
				break;
			}
			memset(buffer, 0, MAXLINE);
			recv_return = recv(connection_fd, buffer, MAXLINE - 1, 0);
		}
		std::cout << "***************** HTTP REQUEST START****************" << std::endl;
		std::cout << requestHandler << std::endl;
		std::cout << "***************** HTTP REQUEST END ****************\n";

		response_handler.load_http_request(requestHandler);
		std::cout << "***************** HTTP REPONSE START****************" << std::endl;
		std::cout << response_handler << std::endl;
		std::cout << "***************** HTTP REPONSE END ****************\n" << std::endl;

		std::string res = response_handler.get_http_response();
		send_ret = send(connection_fd, res.c_str(), res.length(), 0);
		if (send_ret < static_cast<int>(res.length()))
		{
			std::cout << "send_ret : " << send_ret << std::endl;
			send_ret = send(connection_fd, res.c_str(), res.length(), 0);
		}
		close(connection_fd);
		std::cout << "CONNECTION CLOSED" << std::endl;
	}
}