//
// Created by dino on 03.03.23.
//

#include "listening_socket.hpp"
#include <errno.h>
typedef int SOCKET;

int main(int ac, char **av)
{
	if (ac != 3)
		return (1);

	char		*IP = av[1];
	int			port = std::atoi(av[2]);
	SOCKET		newSocket;
	std::string clientAdresse;

	Socket 		sokt(port);

//	int error = errno;
	std::cout << "IP = " << IP << " port = " << port << std::endl;

	while (1)
	{
		if (sokt.select_it() == -1) {
			std::cout << "Erreur select pour accept: " << sokt.select_it() << std::endl;
			break;
		}
		else if (sokt.select_it() > 0) {
			// Accepte une connexion entrante.
			if ((newSocket = sokt.accept_it()) == -1)
				break;
			else {
				// Permet de récupérer l'adresse IP d'un socket, IPv4 ou IPv6, sous forme lisible.
				clientAdresse = sokt.IP_recept();
				std::cout << "client addresse = " << clientAdresse << ": " << sokt.get_struct().sin_port << std::endl;
			}
		}
	}
	// Ferme le socket.
	sokt.close_skt();
	return (0);
}
