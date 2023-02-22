#include "../../inc/httpParser.hpp"
#include "../../inc/trim.hpp"

HttpParser::HttpParser(){};
HttpParser::~HttpParser(){};

void
HttpParser::parseBuffer(char *buff)
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

void
HttpParser::parseFirstLine(std::string firstLine)
{
	char *token = new char[firstLine.length() + 1];
	strcpy(token, firstLine.c_str());
	char *splitedToken = strtok(token, " ");
	int	  counter = 0;
	while (splitedToken != NULL)
	{
		if (counter == 0)
		{
			_http_req["Method"] = splitedToken;
		}
		else if (counter == 1)
		{
			_http_req["Request Target"] = splitedToken;
		}
		else
		{
			_http_req["Protocol"] = splitedToken;
		}
		splitedToken = strtok(NULL, " ");
		counter++;
	}
};

void
HttpParser::parseOtherLines(std::vector<std::string> tmpVector)
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
		if (trim(key).length() != 0 || trim(value).length() != 0)
			_http_req[trim(key)] = trim(value);
	}

	this->print_http_req();
};

void
HttpParser::print_http_req()
{
	std::map<std::string, std::string>::iterator it;
	for (it = _http_req.begin(); it != _http_req.end(); it++)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
};