#include "cluster.hpp"

Cluster::Cluster(void) {}

Cluster::~Cluster(void) {}

void
Cluster::create_upload_folder(json::Value &config)
{
	std::string website_path(config.get("path").get<std::string>() + "/uploads");

	mkdir(website_path.c_str(), S_IRWXU);
}

void
Cluster::load_cluster(json::t_object *config)
{
	json::Value val(config);
	create_upload_folder(val);

	t_host_port new_server;

	new_server.port = val.get("port").get<double>();
	new_server.path = val.get("path").get<std::string>();
	new_server.host = "";
	_servers_vector.push_back(new_server);
	setup();
}

void
Cluster::setup()
{
	FD_ZERO(&_master_fd_set);
	_max_fd = 0;
	for (std::vector<t_host_port>::iterator it(_servers_vector.begin()); it != _servers_vector.end(); it++)
	{
		int	   fd;
		Socket new_socket(AF_INET, it->port, SOCK_STREAM, 0, it->path);
		fd = new_socket.get_socket_id();
		FD_SET(fd, &_master_fd_set);
		_sockets.insert(std::make_pair(fd, new_socket));
		if (fd > _max_fd)
			_max_fd = fd;
		std::cout << it->host << ":" << it->port << " set up" << std::endl;
	}
}

void
Cluster::run()
{
	int end_server = 0;
	while (end_server == 0)
	{
		fd_set reading_set;
		int	   select_return = 0;

		while (select_return == 0)
		{
			std::cout << "select while loop" << std::endl;
			FD_ZERO(&reading_set);
			std::memcpy(&reading_set, &_master_fd_set, sizeof(_master_fd_set));
			std::cout << "waiting for select" << std::endl;
			select_return = select(_max_fd + 1, &reading_set, NULL, NULL, NULL);
		}
		if (select_return > 0)
		{
			// one or more socket_fd is ready to be read.
			for (std::map<int, Socket>::iterator it = _sockets.begin(); it != _sockets.end(); it++)
			{
				std::cout << "trying to accept" << std::endl;

				if (FD_ISSET(it->first, &reading_set))
				{
					int new_sd;

					new_sd = it->second.socket_accept();
					std::cout << "Accepted" << std::endl;
					if (new_sd < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							std::cerr << "Error with accept() " << std::endl;
							end_server = 1;
						}
						break;
					}
					_sockets_accepted.insert(std::make_pair(new_sd, it->second));
					FD_SET(new_sd, &reading_set);
					if (new_sd > _max_fd)
						_max_fd = new_sd;
				}
			}

			for (std::map<int, Socket>::iterator it = _sockets_accepted.begin();
				 it != _sockets_accepted.end(); it++)
			{
				std::cout << "trying to read" << std::endl;
				if (FD_ISSET(it->first, &reading_set))
				{
					std::cout << "is set" << std::endl;
					std::cout << "CONNECTION ID OUTSIDE SOCKET: " << it->first << std::endl;
					int ret;

					ret = it->second.socket_recv();
					std::cout << "ret: " << ret << std::endl;
					if (errno == EWOULDBLOCK)
						std::cout << "ret: EWOULDBLOCK" << std::endl;
					if (ret == 0)
					{
						FD_CLR(it->first, &reading_set);
						it = _sockets_accepted.begin();
					}
				}
			}
		}
		else if (select_return < 0)
		{
			// problem with select, cleaning up.
			std::cerr << "Error with select()" << std::endl;
			_servers_vector.clear();
			_sockets.clear();
			end_server = 1;
		}
	}
}

// EWOULDBLOCK cannot check it?
//  how to check it again?
// maybe arr or ready to read  and pop it if finished?