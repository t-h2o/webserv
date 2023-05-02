#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <map>
#include <string.h>
#include <string>
#include <vector>

namespace http
{

class Request
{
  public:
	typedef std::map<std::string, std::string> t_object;

	Request();
	~Request();

	int				parse_buffer(std::string);
	bool			method_is_authorized(std::string method) const;
	int				error_code;
	std::string		get_method() const;
	std::string		get_path() const;
	std::string		get_protocol() const;
	std::string		get_host() const;
	bool			get_file_exist() const;
	bool			get_has_query() const;
	void			set_query_false();
	void			set_max_content_length(unsigned long);
	const t_object &get_map() const;
	std::string		trim(const std::string &s);
	t_object		_request_map;

  private:
	unsigned long 	_max_content_length;
	bool _has_query;
	int	 parse_first_line(std::string firstLine);
	void parse_other_lines(std::vector<std::string> tmp_vector);
	void clean_content_type();
	void check_if_has_query();
	void clean_path();
	void empty_path_handler();
	int	 check_header();
};

std::ostream &operator<<(std::ostream &, Request const &);

}; /* namespace http */

#endif
