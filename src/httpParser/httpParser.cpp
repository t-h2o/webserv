#include "HttpParser.hpp"

HttpParser::HttpParser(){};
HttpParser::~HttpParser(){};

void HttpParser::parseBuffer(char *buff)
{
	std::vector<std::string> tmpVector;
	std::string				 str_buff = buff;
	std::string				 delimiter = "\r\n";
	std::string				 str;
	int						 delimiter_position = str_buff.find(delimiter);
	while (delimiter_position != -1)
	{
		str = str_buff.substr(0, delimiter_position);
		tmpVector.push_back(str);
		str_buff.erase(str_buff.begin(), str_buff.begin() + delimiter_position + 1);
		delimiter_position = str_buff.find(delimiter);
	}
	this->parseFirstLine(tmpVector[0]);
	this->parseOtherLines(tmpVector);
};

void HttpParser::parseFirstLine(std::string firstLine)
{
	std::vector<std::string> tmpVector;
	std::string delimiter = " ";
	std::string str;
	int delimiter_position = firstLine.find(delimiter);
	while (delimiter_position != -1)
	{
		str = firstLine.substr(0, delimiter_position);
		tmpVector.push_back(this->trim(str));
		firstLine.erase(firstLine.begin(), firstLine.begin() + delimiter_position + 1);
		delimiter_position = firstLine.find(delimiter);
	}
	tmpVector.push_back(this->trim(firstLine));

	if (tmpVector.size() != 3) return;
	_http_req["Method"] = tmpVector[0];
	_http_req["Path"] = tmpVector[1];
	_http_req["Protocol"] = tmpVector[2];
};

void HttpParser::parseOtherLines(std::vector<std::string> tmpVector)
{
	std::string delimiter = ":";
	std::string key;
	std::string value;
	int			delimiter_position;
	for (size_t i = 1; i < tmpVector.size(); i++)
	{
		delimiter_position = tmpVector[i].find(delimiter);
		key = tmpVector[i].substr(0, delimiter_position);
		value = tmpVector[i].substr(delimiter_position + 1);
		if (HttpParser::trim(key).length() != 0 || HttpParser::trim(value).length() != 0)
			_http_req[HttpParser::trim(key)] = HttpParser::trim(value);
	}
};

std::string HttpParser::trim(const std::string &s)
{
	const std::string _WHITESPACE = " \n\r\t\f\v";
	std::string leftTrimedString = "";
	size_t start;
	size_t end;
	start = s.find_first_not_of(_WHITESPACE);
	if (start == std::string::npos) {
		return leftTrimedString;
	} else {
		leftTrimedString = s.substr(start);
	}
	end = leftTrimedString.find_last_not_of(_WHITESPACE);
	return leftTrimedString.substr(0, end + 1);
}

void HttpParser::printHttpReq()
{
	std::map<std::string, std::string>::iterator it;
	for (it = _http_req.begin(); it != _http_req.end(); it++)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
};

std::string HttpParser::getMethod() const {
	return _http_req.at("Method");
};

std::string HttpParser::getPath() const {
	return _http_req.at("Path");
};

std::string HttpParser::getProtocol() const {
	return _http_req.at("Protocol");
};