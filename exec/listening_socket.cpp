//
// Created by dino on 03.03.23.
//

#include "listening_socket.hpp"

int main(int ac, char **av)
{
	sockaddr_in addr;
	Socket sokt(socket(AF_UNIX, SOCK_STREAM, 0));

	sokt.get_new_s();
	sokt.bind_it(&addr);
	return (0);
}