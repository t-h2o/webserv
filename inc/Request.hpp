#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <map>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <vector>

namespace http
{

class Request
{
  public:
	typedef std::map<std::string, std::string> t_object;

	Request();
	~Request();

	void			parse_buffer(std::string);
	bool			method_is_authorized(std::string method) const;
	std::string		get_method() const;
	std::string		get_path() const;
	std::string		get_protocol() const;
	std::string		get_host() const;
	bool			get_file_exist() const;
	bool			get_has_query() const;
	void			set_query_false();
	const t_object &get_map() const;
	int				get_error_code() const;
	void			set_error_code(int);
	std::string		trim(const std::string &s);
	t_object		_request_map;

  private:
	int	 _error_code;
	bool _has_query;
	void parse_first_line(std::string firstLine);
	void parse_other_lines(std::vector<std::string> tmp_vector);
	void clean_content_type();
	void check_if_has_query();
	void clean_path();
	void empty_path_handler();
	void check_header();
	void check_path_and_method();
};

std::ostream &operator<<(std::ostream &, Request const &);

}; /* namespace http */

#endif
