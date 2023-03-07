//
// Created by dino on 03.03.23.
//

#ifndef WEBSERV_LISTENING_SOCKET_H
#define WEBSERV_LISTENING_SOCKET_H

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

typedef int SOCKET;

struct Client {
	SOCKET 		sckt;
	sockaddr_in	addr;
};

class Socket
{
private:
	SOCKET 	_s;
	int		_bind_it;
	int		_listen_it;
	int 	_its_close;
	struct sockaddr_in _address;

public:

	Socket(int port) : _s(0), _bind_it(0), _listen_it(0), _its_close(0) {

		_address.sin_addr.s_addr = INADDR_ANY; // indique que toutes les sources seront acceptées
		_address.sin_port = htons(port); // toujours penser à traduire le port en réseau
		_address.sin_family = AF_INET;

		// Crée un socket avec les paramètres passés.
		create_socket();
//		// Connecte un socket précédemment créé au serveur passé en paramètre.
//		is_connected(server);
		// La fonction bind est utilisée pour assigner une adresse locale à un socket.
		bind_it();
		// Place le socket dans un état lui permettant d'écouter les connexions entrantes.
		listen_it();
	}

	void	create_socket(void) {
		if ((_s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
			std::cout << _s << " socket creation error\n";
		std::cout << "socket creation: " << _s << std::endl;
	}

//	void	is_connected(sockaddr_in *server) {
//		if (connect(_s, (const struct sockaddr*)&server, sizeof (server)) != 0)
//			std::cout << "connect fail\n";
//	}

	void	bind_it(void) {
		if ((_bind_it = bind(_s, (struct sockaddr *)&_address, sizeof(_address))) != 0)
			std::cout << _bind_it << " bad bind access\n";
	}

	void	listen_it(void) {
		if ((_listen_it = listen(_s, SOMAXCONN)) != 0)
			std::cout << _listen_it << " bad listen access\n";
		std::cout << "listen: " << _listen_it << std::endl;
	}

	int	accept_it(void) {
		socklen_t len = sizeof(_address);
		return (accept(_s, (struct sockaddr *)&_address, &len));
	}

	const char	*IP_recept() {
		char IP_c[INET6_ADDRSTRLEN];
		return (inet_ntop(_address.sin_family, (void*)&(_address.sin_addr), IP_c, INET6_ADDRSTRLEN));
	}

	void	close_skt(void) {
		if ((_its_close = close(_s))  != 0)
			std::cout << _its_close << " close fail\n";
	}

	void	get_s(void) {
		std::cout << _s << std::endl;
	}
	~Socket(void) {}

	struct sockaddr_in get_struct(void) {
		return (_address);
	}
//	class myexception: public exception
//	{
//		virtual const char* what() const throw()
//		{
//			return "My exception happened";
//		}
//	} myex;
};
#endif //WEBSERV_LISTENING_SOCKET_H
