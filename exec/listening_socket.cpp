//
// Created by dino on 03.03.23.
//

#include "listening_socket.hpp"
#include <errno.h>
typedef int SOCKET;
//#define inet_pton(FAMILY, IP, PTR_STRUCT_SOCKADDR) (*(PTR_STRUCT_SOCKADDR)) = inet_addr((IP))
//typedef unsigned int socklen_t;
//#include <sys/socket.h>
//#include <netinet/in.h> // sockaddr_in, IPPROTO_TCP
//#include <arpa/inet.h> // hton*, ntoh*, inet_addr
//#include <unistd.h>  // close
//#include <cerrno> // errno
//#define SOCKET int
//#define INVALID_SOCKET ((int)-1)
//bool closesocket(SOCKET socket);

int main(int ac, char **av)
{
	if (ac != 3)
		return (1);

	char		*IP = av[1];
	int			port = std::atoi(av[2]);
	SOCKET		newSocket;
	std::string clientAdresse;

//	sockaddr_in server;
//	server.sin_addr.s_addr = inet_addr(IP);
//	server.sin_family = AF_INET;
//	server.sin_port = port;

	Socket 		sokt(port);

//	int error = errno;

	std::cout << "IP = " << IP << " port = " << port << std::endl;

	while (1)
	{
		// Accepte une connexion entrante.
		if ((newSocket = sokt.accept_it()) == -1)
			break ;
		else
		{
			// Permet de récupérer l'adresse IP d'un socket, IPv4 ou IPv6, sous forme lisible.
			clientAdresse = sokt.IP_recept();
			std::cout << "client addresse = " << clientAdresse << ": " << sokt.get_struct().sin_port << std::endl;
		}
	}
	// Ferme le socket.
	sokt.close_skt();
	return (0);
}
