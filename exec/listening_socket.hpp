//
// Created by dino on 03.03.23.
//

#ifndef WEBSERV_LISTENING_SOCKET_H
#define WEBSERV_LISTENING_SOCKET_H

#include <iostream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

class Socket
{
private:
	int _new_s;
	int _bind_it;

public:
	Socket(void) : _new_s(0), _bind_it(0) {}
	Socket(const int& socket_fct)
	: _new_s(socket_fct), _bind_it(0) {}

	void	bind_it(sockaddr_in *addr) {
		addr->sin_addr.s_addr = INADDR_ANY; // indique que toutes les sources seront acceptées
		addr->sin_port = htons(0); // toujours penser à traduire le port en réseau
		addr->sin_family = AF_INET;

		if ((_bind_it = bind(_new_s, (sockaddr*)&addr, sizeof(addr))) != 0)
			std::cout << _bind_it << " bad bind access\n";
	}

	void	get_new_s(void) {
		std::cout << _new_s << std::endl;
	}
	~Socket(void) {}

//	class myexception: public exception
//	{
//		virtual const char* what() const throw()
//		{
//			return "My exception happened";
//		}
//	} myex;
};
#endif //WEBSERV_LISTENING_SOCKET_H
