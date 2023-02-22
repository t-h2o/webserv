#ifndef HTTPPARSER_HPP
#define HTTPPARSER_HPP

#include <iostream>
#include <map>
#include <string.h>
#include <string>
#include <vector>

class HttpParser
{
  private:
	std::map<std::string, std::string> _http_req;

  public:
	HttpParser();
	~HttpParser();
	void		parseBuffer(char *buff);
	void		parseFirstLine(std::string firstLine);
	void		parseOtherLines(std::vector<std::string> tmpVector);
	std::string trim(const std::string &s);
	std::string ltrim(const std::string &s);
	std::string rtrim(const std::string &s);
	void		print_http_req();
};

#endif