#include "httpRequest.hpp"

HttpRequest::HttpRequest(){};
HttpRequest::~HttpRequest(){};

void
HttpRequest::parseBuffer(char *buff)
{
	std::vector<std::string> tmp_vector;
	std::string				 str_buff = buff;
	std::string				 delimiter = "\r\n";
	std::string				 str;
	int						 delimiter_position = str_buff.find(delimiter);

	while (delimiter_position != -1)
	{
		str = str_buff.substr(0, delimiter_position);
		tmp_vector.push_back(str);
		str_buff.erase(str_buff.begin(), str_buff.begin() + delimiter_position + 1);
		delimiter_position = str_buff.find(delimiter);
	}
	if (str_buff.length() != 0)
	{
		_request_map["Body"] = this->trim(str_buff);
	}
	this->parseFirstLine(tmp_vector[0]);
	this->parseOtherLines(tmp_vector);
}

void
HttpRequest::parseFirstLine(std::string firstLine)
{
	std::vector<std::string> tmp_vector;
	std::string				 delimiter = " ";
	std::string				 str;
	int						 delimiter_position = firstLine.find(delimiter);
	while (delimiter_position != -1)
	{
		str = firstLine.substr(0, delimiter_position);
		tmp_vector.push_back(this->trim(str));
		firstLine.erase(firstLine.begin(), firstLine.begin() + delimiter_position + 1);
		delimiter_position = firstLine.find(delimiter);
	}
	tmp_vector.push_back(this->trim(firstLine));

	if (tmp_vector.size() != 3)
		return;
	_request_map["Method"] = tmp_vector[0];
	_request_map["Path"] = tmp_vector[1];
	_request_map["Protocol"] = tmp_vector[2];
}

void
HttpRequest::parseOtherLines(std::vector<std::string> tmp_vector)
{
	std::string delimiter = ":";
	std::string key;
	std::string value;
	int			delimiter_position;
	for (size_t i = 1; i < tmp_vector.size(); i++)
	{
		delimiter_position = tmp_vector[i].find(delimiter);
		key = tmp_vector[i].substr(0, delimiter_position);
		value = tmp_vector[i].substr(delimiter_position + 1);
		if (HttpRequest::trim(key).length() != 0 || HttpRequest::trim(value).length() != 0)
			_request_map[HttpRequest::trim(key)] = HttpRequest::trim(value);
	}
}

std::string
HttpRequest::trim(const std::string &s)
{
	const std::string _WHITESPACE = " \n\r\t\f\v";
	std::string		  left_trimed_string = "";
	size_t			  start;
	size_t			  end;
	start = s.find_first_not_of(_WHITESPACE);
	if (start == std::string::npos)
	{
		return left_trimed_string;
	}
	else
	{
		left_trimed_string = s.substr(start);
	}
	end = left_trimed_string.find_last_not_of(_WHITESPACE);
	return left_trimed_string.substr(0, end + 1);
}

void
HttpRequest::printHttpReq()
{
	for (std::map<std::string, std::string>::iterator it = _request_map.begin(); it != _request_map.end(); it++)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
}

std::string
HttpRequest::getMethod() const
{
	return _request_map.at("Method");
}

std::string
HttpRequest::getPath() const
{
	return _request_map.at("Path");
}

std::string
HttpRequest::getProtocol() const
{
	return _request_map.at("Protocol");
}

std::string
HttpRequest::getHost() const
{
	return _request_map.at("Host");
}

bool
HttpRequest::methodIsAuthorized(std::string method) const
{
	return (method.compare("GET") == 0 || method.compare("POST") == 0 || method.compare("DELETE") == 0);
}
