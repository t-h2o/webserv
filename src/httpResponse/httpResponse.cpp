#include "httpResponse.hpp"

HttpResponse::HttpResponse(void){};

HttpResponse::~HttpResponse(void){};

void
HttpResponse::init_response_map(void)
{
	_response_map["Status-line"] = "";
	_response_map["Date"] = "";
	_response_map["Server"] = "Webserver";
	_response_map["Content-Length"] = "";
	_response_map["Content-Type"] = "";
	_response_map["Connection"] = "close";
	_response_map["Protocol"] = "HTTP/1.1 ";
	_response_map["header-string"] = "";
	_response_map["body-string"] = "";
	_response_map["full-reponse-string"] = "";
	_response_map["dir_location"] = "/Users/rburri/Desktop/network_cpp/server_lib";
};

void
HttpResponse::load_response_map(int status_code)
{
	_response_map["Date"] += get_time_stamp();
	_response_map["Status-line"]
		= _response_map["Protocol"] + _status_code.get_key_value_formated(status_code);
	_response_map["dir_location"] += _request_path;
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
HttpResponse::count_file_size(std::string path)
{
	std::ifstream stream;
	if (file_exists(path))
	{
		stream.open(path.c_str(), std::ios::binary);
		stream.seekg(0, std::ios::end);
		_body_size = stream.tellg();
		std::cout << "file.html length : " << _body_size << std::endl;
		stream.close();
	}
}

bool
HttpResponse::file_exists(std::string path)
{
	std::ifstream file;
	bool		  ret = false;
	file.open(path.c_str());
	if (file)
	{
		ret = true;
		file.close();
	}
	return ret;
}

void
HttpResponse::set_response_type(std::string path, std::string type = "")
{
	if (type != "")
	{
		_response_map["Content-Type"] = type;
	}
	type = path.substr(path.rfind(".") + 1, path.size() - path.rfind("."));
	if (type == "html")
		_response_map["Content-Type"] = "text/html";
	else if (type == "css")
		_response_map["Content-Type"] = "text/css";
	else if (type == "js")
		_response_map["Content-Type"] = "text/javascript";
	else if (type == "jpeg" || type == "jpg")
		_response_map["Content-Type"] = "image/jpeg";
	else if (type == "png")
		_response_map["Content-Type"] = "image/png";
	else if (type == "bmp")
		_response_map["Content-Type"] = "image/bmp";
	else
		_response_map["Content-Type"] = "text/plain";
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

void
HttpResponse::load_http_request(HttpRequest &req)
{
	_request_path = req.getPath();
	std::cout << " Request Path: " << _request_path << std::endl;
	response_handler();
}

void
HttpResponse::load_content_length(void)
{
	_response_map["Content-Length"] = std::to_string(_body_size);
}

void
HttpResponse::response_handler(void)
{
	init_response_map();
	// CHECKER HERE
	// 200 OK for now
	set_response_type(_request_path);
	load_response_map(200);
	count_file_size(_response_map["dir_location"]);
	load_content_length();
	construct_header_string();
}

void
HttpResponse::construct_header_string(void)
{
	std::string CRLF = "\r\n";

	_response_map["header-string"] += _response_map["Status-line"];
	_response_map["header-string"] += CRLF;
	_response_map["header-string"] += "Date: " + _response_map["Date"];
	_response_map["header-string"] += CRLF;
	_response_map["header-string"] += "Server: " + _response_map["Server"];
	_response_map["header-string"] += CRLF;
	_response_map["header-string"] += "Content-Length: " + _response_map["Content-Length"];
	_response_map["header-string"] += CRLF;
	_response_map["header-string"] += "Content-Type: " + _response_map["Content-Type"];
	_response_map["header-string"] += CRLF;
	_response_map["header-string"] += "Connection: " + _response_map["Connection"];
	_response_map["header-string"] += CRLF;
	_response_map["header-string"] += CRLF;
}
