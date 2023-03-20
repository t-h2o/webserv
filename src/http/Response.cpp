#include "Response.hpp"

namespace http
{

Response::Response(void) {}

Response::~Response(void) {}

void
Response::load_http_request(Request &req)
{
	init_response_map();
	std::string requested_path = req.getPath();
	_response_map["dir_location"] += requested_path;
	std::cout << "dir_location at load_HTTP_REQUEST : " << _response_map["dir_location"] << std::endl;
	std::cout << "METHOD: " << req.getMethod() << "\nAuth: " << req.methodIsAuthorized(req.getMethod())
			  << std::endl;
	if (!req.methodIsAuthorized(req.getMethod()))
	{
		load_response_map(405);
	}
	else if (!file_exists(_response_map["dir_location"]))
	{
		load_response_map(404);
	}
	else
	{
		load_response_map(200);
	}
}

void
Response::init_response_map(void)
{
	_response_map["Status-line"] = "";
	_response_map["Date"] = "";
	_response_map["Server"] = "Webserver";
	_response_map["Content-Length"] = "";
	_response_map["Content-Type"] = "";
	_response_map["Connection"] = "Closed";
	_response_map["Protocol"] = "HTTP/1.1 ";
	_response_map["header-string"] = "";
	_response_map["body-string"] = "";
	_response_map["full-response-string"] = "";
	_response_map["dir_location"] = "/Users/rburri/Desktop/network_cpp";
}

void
Response::load_response_map(int status_code)
{
	_response_map["Date"] += get_time_stamp();
	_response_map["Status-line"]
		= _response_map["Protocol"] + _status_code.get_key_value_formated(status_code);
	if (status_code != 200)
	{
		set_response_type(".html");
		create_error_html_page(status_code);
	}
	else
	{
		set_response_type(_response_map["dir_location"]);
		construct_body_string(_response_map["dir_location"]);
	}
	set_content_length(_response_map["body-string"]);
	construct_header_string();
	construct_full_response();
}

std::string
Response::get_time_stamp(void)
{
	std::time_t stamp = std::time(NULL);
	std::string formated_date = std::asctime(std::gmtime(&stamp));
	formated_date = formated_date.substr(0, formated_date.length() - 1);
	formated_date += " GMT";
	return formated_date;
}

void
Response::set_content_length(std::string str)
{
	std::stringstream ss;
	ss << str.length();
	_response_map["Content-Length"] = ss.str();
}

bool
Response::file_exists(std::string path)
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
Response::set_response_type(std::string path)
{
	std::string type = "";
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
	else if (type == "ico")
		_response_map["Content-Type"] = "image/x-icon";
	else
		_response_map["Content-Type"] = "text/plain";
}

void
Response::construct_header_string(void)
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

void
Response::construct_body_string(std::string path_to_file)
{
	std::ifstream	  file;
	std::stringstream buffer;

	file.open(path_to_file.c_str());
	if (file.fail())
	{
		std::cout << "Open file error" << std::endl;
		return;
	}
	buffer << file.rdbuf();
	_response_map["body-string"] = buffer.str();
	file.close();
}

void
Response::construct_full_response(void)
{
	_response_map["full-response-string"] += _response_map["header-string"];
	_response_map["full-response-string"] += _response_map["body-string"];
}

std::string
Response::get_http_response(void)
{
	std::string ret;
	ret = _response_map["full-response-string"];
	return ret;
}

void
Response::create_error_html_page(int code)
{
	std::stringstream ss;
	ss << code;
	std::string html_page = "";
	html_page += "<!DOCTYPE html><html><head><link rel=\"stylesheet\"href=\"style.css\"/><link rel=\"icon\" "
				 "href=\"favicon.ico\"><title>";
	html_page += ss.str();
	html_page
		+= "</title></head><body><div class=\" wrapper\"><div class=\"centered-box\"><h1 class=\"title\">";
	html_page += _status_code.get_key_value_formated(code);
	html_page += "</h1></div></div></body></html>";
	_response_map["body-string"] = html_page;
	std::cout << "AUTO_HTML PAGE:\n" << html_page << std::endl;
}

std::ostream &
operator<<(std::ostream &output, Response const &res)
{
	Response::t_object::const_iterator start;

	for (start = res.get_map().begin(); start != res.get_map().end(); ++start)
	{
		output << start->first << " : " << start->second << "\n";
	}
	return output;
}

const Response::t_object &
Response::get_map() const
{
	return _response_map;
}

} /* namespace http */
