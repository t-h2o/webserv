#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include "Json.hpp"
#include "Socket.hpp"
#include <cstring>
#include <iostream>
#include <map>
#include <sys/stat.h>
#include <vector>

class Cluster
{
  public:
	Cluster(void);
	~Cluster(void);
	void load_cluster(json::t_object *config);
	void setup();
	void run();
	void create_upload_folder(json::Value &config);
	typedef struct host_port
	{
		double		port;
		std::string host;
		std::string path;
	} t_host_port;

  private:
	std::vector<t_host_port> _servers_vector;
	// map of socket_fd and the socket itself
	std::map<int, Socket> _sockets;
	fd_set				  _master_fd_set;
	int					  _max_fd;
};

#endif
