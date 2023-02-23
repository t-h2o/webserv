#ifndef HTTPPARSER_HPP
#define HTTPPARSER_HPP

#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>

class HttpParser
{
private:
	std::map<std::string, std::string> _http_req;
	void parseFirstLine(std::string firstLine);
	void parseOtherLines(std::vector<std::string> tmpVector);

public:
	HttpParser();
	~HttpParser();
	
	void parseBuffer(char *buff);
	std::string trim(const std::string &s);
	void printHttpReq();
	// getters
	std::string getMethod() const;
	std::string getPath() const;
	std::string getProtocol() const;
};

#endif