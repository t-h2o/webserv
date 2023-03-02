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
	void load_http_request(HttpRequest &req);
	void print_response_map(void);
	void init_response_map(void);

  private:
	std::map<std::string, std::string> _response_map;
	StatusCode						   _status_code;
	HttpRequest						   _request;
	std::string						   _request_path;
	int								   _body_size;

	void		response_handler(void);
	void		set_response_type(std::string path, std::string type);
	bool		file_exists(std::string path);
	void		load_content_length(void);
	void		load_response_map(int status_code);
	std::string get_time_stamp(void);
	void		count_file_size(std::string path);
	void		construct_header_string(void);
};

#endif