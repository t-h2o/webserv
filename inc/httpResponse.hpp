#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include "statusCodes.hpp"
#include <fstream>
#include <string>

class HttpResponse
{
  public:
	HttpResponse(void);
	~HttpResponse(void);
	std::string get_time_stamp(void);
	int			count_file_size(std::string path);
	void		init_response_map(void);
	void		load_response_map(int status_code);
	void		print_response_map(void);
	bool		file_exists(std::string path);
	void set_response_type(std::string path, std::string type);

  private:
	std::map<std::string, std::string> _response_map;
	StatusCode						   _status_code;
	// std::string _full_response;
	// size_t _header_size;
	// size_t _body_size;
	// size_t _total_size;
	// std::string _date;
};

#endif

/*
	Date: Sun, 06 Nov 1994 08:49:37 GMT
	Server: webserver
	Content-Length:
	Content-Type:
	Connection: Closed
	Transfer-Encoding: chunked => ????
*/