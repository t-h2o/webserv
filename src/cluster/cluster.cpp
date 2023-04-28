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
		fd = new_socket.get_sock_id();
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
			FD_ZERO(&reading_set);
			std::memcpy(&reading_set, &_master_fd_set, sizeof(_master_fd_set));
			std::cout << "waiting for select" << std::endl;
			select_return = select(_max_fd + 1, &reading_set, NULL, NULL, NULL);
		}
		if (select_return > 0)
		{
			// one or more socket_fd is ready to be read.
			int desc_ready = select_return;
			for (int i = 0; i <= _max_fd && desc_ready > 0; ++i)
			{
				if (FD_ISSET(i, &reading_set))
				{
					desc_ready--;
					std::map<int, Socket>::iterator sock = _sockets.find(i);
					if (sock != _sockets.end())
					{

						int new_sd = sock->second.socket_accept();
						if (new_sd < 0)
						{
							if (errno != EWOULDBLOCK)
							{
								perror("  accept() failed");
							}
							break;
						}
					}

					// std::cout << "accepted" << std::endl;
					// it->second.socket_recv();
					// std::cout << "recv ended" << std::endl;
					// FD_CLR(it->first, &reading_set);
					// it = _sockets.begin();
					// break;
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
