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
	HttpRequest();
	virtual ~HttpRequest();

	void		parseBuffer(char *buff);
	void		printHttpReq();
	// Getters
	std::string getMethod() const;
	std::string getPath() const;
	std::string getProtocol() const;
	std::string getHost() const;

  private:
	bool		methodIsAuthorized(std::string method) const;
	std::string trim(const std::string &s);
	std::map<std::string, std::string> _request_map;
	void							   parseFirstLine(std::string firstLine);
	void							   parseOtherLines(std::vector<std::string> tmp_vector);
};

#endif