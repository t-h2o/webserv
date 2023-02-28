#include "httpResponse.hpp"

HttpResponse::HttpResponse(void) { init_response_map(); };

HttpResponse::~HttpResponse(void){};

void
HttpResponse::init_response_map(void)
{
	_response_map["Status-line"] = "";
	_response_map["Date"] = "";
	_response_map["Server"] = "Webserver";
	_response_map["Content-Length"] = "";
	_response_map["Content-Type"] = "";
	_response_map["Connection"] = "";
	_response_map["Protocol"] = "HTTP/1.1 ";
};

void
HttpResponse::load_response_map(int status_code)
{
	_response_map["Date"] += get_time_stamp();
	_response_map["Status-line"]
		= _response_map["Protocol"] + _status_code.get_key_value_formated(status_code);
}

std::string
HttpResponse::get_time_stamp(void)
{
	std::time_t stamp = std::time(NULL);
	std::string formated_date = std::asctime(std::gmtime(&stamp));
	formated_date = formated_date.substr(0, formated_date.length() - 1);
	formated_date += " GMT";
	return formated_date;
}

void
HttpResponse::print_response_map(void)
{
	std::map<std::string, std::string>::iterator it;
	for (it = _response_map.begin(); it != _response_map.end(); it++)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
}

int
HttpResponse::count_file_size(std::string path)
{
	std::ifstream stream;
	int			  size;
	stream.open(path.c_str(), std::ios::binary);
	stream.seekg(0, std::ios::end);
	size = stream.tellg();
	return size;
}

bool
HttpResponse::file_exists(std::string path)
{
	std::ifstream file;
	bool		  ret = false;
	file.open(path);
	if (file)
	{
		ret = true;
		file.close();
	}
	return ret;
}