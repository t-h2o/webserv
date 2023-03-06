#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include "statusCodes.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "httpRequest.hpp"

class HttpResponse
{
  public:
	HttpResponse();
	virtual ~HttpResponse(void);
	std::string get_http_response(void);
	void		print_response_map(void);
	void		load_http_request(HttpRequest &req);

  private:
	std::map<std::string, std::string> _response_map;
	StatusCode						   _status_code;
	HttpRequest						   _request;
	std::string						   _request_path;

	void		load_content_length(std::string str);
	void		init_response_map(void);
	void		response_handler(void);
	void		set_response_type(std::string path);
	bool		file_exists(std::string path);
	void		load_response_map(int status_code);
	std::string get_time_stamp(void);
	void		construct_header_string(void);
	void		construct_body_string(std::string path_to_file);
	void		construct_full_response(void);
};

#endif