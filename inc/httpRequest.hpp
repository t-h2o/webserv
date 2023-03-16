#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <iostream>
#include <map>
#include <string.h>
#include <string>
#include <vector>

class HttpRequest
{
  public:
	typedef std::map<std::string, std::string> t_object;

	HttpRequest();
	~HttpRequest();

	void parseBuffer(std::string);
	bool methodIsAuthorized(std::string method) const;
	// Getters
	std::string getMethod() const;
	std::string getPath() const;
	std::string getProtocol() const;
	std::string getHost() const;
	const t_object &get_map() const;

  private:
	t_object 	_request_map;
	std::string trim(const std::string &s);
	void		parseFirstLine(std::string firstLine);
	void		parseOtherLines(std::vector<std::string> tmp_vector);
};

std::ostream &operator<<(std::ostream &, HttpRequest const &);

#endif
