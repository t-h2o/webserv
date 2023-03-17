#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <map>
#include <string.h>
#include <string>
#include <vector>

namespace http {

class Request
{
  public:
	typedef std::map<std::string, std::string> t_object;

	Request();
	~Request();

	void parse_buffer(std::string);
	bool method_is_authorized(std::string method) const;
	// Getters
	std::string get_method() const;
	std::string get_path() const;
	std::string get_protocol() const;
	std::string get_host() const;
	const t_object &get_map() const;

  private:
	t_object 	_request_map;
	std::string trim(const std::string &s);
	void		parse_first_line(std::string firstLine);
	void		parse_other_lines(std::vector<std::string> tmp_vector);
};

std::ostream &operator<<(std::ostream &, Request const &);

}; /* namespace http */

#endif
