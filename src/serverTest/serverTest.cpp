#include "serverTest.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Socket.hpp"
#include "Value.hpp"
#include <cstring>
#include <vector>

#include <sys/stat.h>

static void
create_upload_folder(json::Value &config)
{
	std::string website_path(config.get("path").get<std::string>() + "/uploads");

	mkdir(website_path.c_str(), S_IRWXU);
}

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
	json::Value server_config;
	server_config.duplicate(val.get("nicesite.com").get<json::t_object>());
	std::cout << server_config << std::endl;
	unsigned short port = server_config.get("port").get<double>();
	Socket		   sock(AF_INET, port, SOCK_STREAM, 0, server_config);

	create_upload_folder(server_config);
	while (1)
	{
		std::cout << "++++++ Waiting for new connection ++++++" << std::endl;

		sock.socket_accept();
		sock.socket_recv();

		std::cout << "CONNECTION CLOSED" << std::endl;
	}
}
