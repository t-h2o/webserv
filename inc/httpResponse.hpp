#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include "statusCodes.hpp"
#include <fstream>
#include <string>
#include <time.h>
#include "httpRequest.hpp"

class HttpResponse
{
public:
	HttpResponse();
	~HttpResponse(void);
	std::string get_time_stamp(void);
	void count_file_size(std::string path);
	void init_response_map(void);
	void load_response_map(int status_code);
	void load_http_request(HttpRequest &req);
	void load_content_length(void);
	void print_response_map(void);
	bool file_exists(std::string path);
	void set_response_type(std::string path, std::string type);
	void response_handler(void);

		private : std::map<std::string, std::string>
					  _response_map;
	StatusCode _status_code;
	HttpRequest _request;
	std::string _request_path;
	// std::string _full_response;
	// size_t _header_size;
	int _body_size;
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

/**
 * TODO => construct header string 
 */