#include "Response.hpp"

namespace http
{

StatusCode Response::_status_code;

Response::Response(void) {}

Response::~Response(void) {}

void
Response::load_http_request(Request &request)
{
	_response_map["dir_location"] += request.get_path();
	if (request.get_method().compare("GET") == 0)
	{
		std::cout << "it's GET" << std::endl;
		if (access(_response_map["dir_location"].c_str(), F_OK))
		{
			load_response_get(404);
		}
		else
		{
			load_response_get(200);
		}
	}
	else if (request.get_method().compare("POST") == 0)
	{
		std::cout << "it's POST\n" << "File name: " << request._request_map["FileName"].c_str()<< std::endl;
		if (request._request_map["FileName"].compare("exist") == 0)
		// this request is not the same as request of Socket!!!
			load_response_post_delete(409);
		else
			load_response_post_delete(201);
			// 409 Conflict
			// 201 Created
	}
	else if (request.get_method().compare("DELETE") == 0)
	{
		std::cout << "it's DELETE" << std::endl;
		if (access(request._request_map["FileName"].c_str(), F_OK))
			load_response_post_delete(204);
		else
			load_response_post_delete(404);
		// 204 No Content
		// 404 Not Found
	}
	else
	{
		load_response_get(405);
	}
	// if (!request.method_is_authorized(request.get_method()))
	// {
	// 	load_response_map(405);
	// }
	// else if (access(_response_map["dir_location"].c_str(), F_OK))
	// {
	// 	load_response_map(404);
	// }
	// else
	// {
	// 	load_response_map(200);
	// }
}

void
Response::init_response_map(const json::Value &config)
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
	_response_map["dir_location"] = config.get("path").get<std::string>();
}

void
Response::load_response_get(int status_code)
{
	_response_map["Date"] = get_time_stamp();
	_response_map["Status-line"]
		= _response_map["Protocol"] + _status_code.get_key_value_formated(status_code);
	if (status_code != 200)
	{
		set_response_type("html");
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

void
Response::load_response_post_delete(int status_code)
{
	_response_map["Date"] = get_time_stamp();
	_response_map["Status-line"]
		= _response_map["Protocol"] + _status_code.get_key_value_formated(status_code);
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
	_response_map["Content-Length"] = std98::to_string(str.length());
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
	else if (type == "json")
		_response_map["Content-Type"] = "application/json";
	else
		_response_map["Content-Type"] = "text/plain";
}

void
Response::construct_header_string(void)
{
	std::string CRLF = "\r\n";

	_response_map["header-string"] = _response_map["Status-line"] + CRLF + "Date: " + _response_map["Date"]
									 + CRLF + "Server: " + _response_map["Server"] + CRLF
									 + "Content-Length: " + _response_map["Content-Length"] + CRLF
									 + "Content-Type: " + _response_map["Content-Type"] + CRLF
									 + "Connection: " + _response_map["Connection"] + CRLF + CRLF;
}

void
Response::construct_body_string(std::string path_to_file)
{
	std::ifstream	  file;
	std::stringstream buffer;

	file.open(path_to_file.c_str());
	if (file.fail())
	{
		std::cerr << "Open file error" << std::endl;
		return;
	}
	buffer << file.rdbuf();
	_response_map["body-string"] = buffer.str();
	file.close();
}

void
Response::construct_full_response(void)
{
	_response_map["full-response-string"] = _response_map["header-string"] + _response_map["body-string"];
}

std::string
Response::get_http_response(void)
{
	return _response_map["full-response-string"];
}

void
Response::create_error_html_page(int code)
{
	_response_map["body-string"]
		= "<!DOCTYPE html><html><head><link rel=\"stylesheet\"href=\"style.css\"/><link rel=\"icon\" "
		  "href=\"favicon.ico\"><title>"
		  + std98::to_string(code)
		  + "</title></head><body><div class=\" wrapper\"><div class=\"centered-box\"><h1 class=\"title\">"
		  + _status_code.get_key_value_formated(code) + "</h1></div></div></body></html>";
}
void
Response::create_text_response()
{
	_response_map["body-string"] = std::string("The file: ") + std::string(" was successfully created");
}

std::ostream &
operator<<(std::ostream &output, Response const &response)
{
	for (Response::t_object::const_iterator start(response.get_map().begin());
		 start != response.get_map().end(); ++start)
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
