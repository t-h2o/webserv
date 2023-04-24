#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "Request.hpp"
#include "StatusCodes.hpp"
#include "Value.hpp"
#include "std98.hpp"
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

namespace http
{

class Response
{
  public:
	typedef std::map<std::string, std::string> t_object;

	Response();
	~Response(void);
	std::string		get_http_response(void);
	void			init_response_map(const json::Value &config);
	void			load_http_request(Request &req);
	const t_object &get_map() const;
	void 		set_dir_path(std::string);

  private:
	static StatusCode _status_code;
	t_object _response_map;
	std::string _dir_path;
	void	 set_content_length(std::string str);
	void	 init_response_map(void);
	void	 set_response_type(std::string path);
	void	 load_response_get(int status_code, std::string path);
	void	 load_response_post_delete(int status_code);

	std::string get_time_stamp(void);
	void		construct_header_string(void);
	void		construct_body_string(std::string path_to_file);
	void		construct_full_response(void);
	void		create_error_html_page(int code);
};

std::ostream &operator<<(std::ostream &, Response const &);

} /* namespace http */

#endif
