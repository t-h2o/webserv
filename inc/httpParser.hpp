#ifndef HTTPPARSER_HPP
#define HTTPPARSER_HPP

#include <map>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>

class HttpParser
{
  private:
	std::map<std::string, std::string> _http_req;

  public:
	HttpParser();
	~HttpParser();
	void parseBuffer(char *buff);
	void parseFirstLine(std::string firstLine);
	void parseOtherLines(std::vector<std::string> tmpVector);
	void print_http_req();
};

#endif