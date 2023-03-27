#include "StatusCodes.hpp"

namespace http
{

StatusCode::StatusCode()
{
	// 1xx Infomatonal
	_status_codes[100] = "Continue";
	_status_codes[101] = "Switching Protocols";
	// 2xx Successful
	_status_codes[200] = "OK";
	_status_codes[201] = "Created";
	_status_codes[202] = "Accepted";
	_status_codes[203] = "Non-Authoritative Information";
	_status_codes[204] = "No Content";
	_status_codes[205] = "Rest Content";
	_status_codes[206] = "Partial Content";
	// 3xx Redirection
	_status_codes[300] = "Multiple Choices";
	_status_codes[301] = "Moved Permanently";
	_status_codes[302] = "Found";
	_status_codes[303] = "See Other";
	_status_codes[304] = "Not Modified";
	_status_codes[305] = "Use Proxy";
	_status_codes[307] = "Temporary Reirect";
	// 4xx Client Error
	_status_codes[400] = "Bad Request";
	_status_codes[401] = "Unauthorized";
	_status_codes[402] = "Payment Required";
	_status_codes[403] = "Forbidden";
	_status_codes[404] = "Not Found";
	_status_codes[405] = "Method Not Allowed";
	_status_codes[406] = "Not Acceptable";
	_status_codes[407] = "Proxy Autentication Required";
	_status_codes[408] = "Request Timout";
	_status_codes[409] = "Conflict";
	_status_codes[410] = "Gone";
	_status_codes[411] = "Length Required";
	_status_codes[412] = "Precondition Failed";
	_status_codes[413] = "Request Entity Too Large";
	_status_codes[414] = "Request-URI Too Long";
	_status_codes[415] = "Unsupported Media Type";
	_status_codes[416] = "Requested Range Not Satisfiable";
	_status_codes[417] = "Expectation Failed";
	// 5xx Error
	_status_codes[500] = "Internal Server Error";
	_status_codes[501] = "Not Implemented";
	_status_codes[502] = "Bad Gateway";
	_status_codes[503] = "Service Unavailable";
	_status_codes[504] = "gateway Timeout";
	_status_codes[505] = "HTTP Version Not Supported";
}

std::string &
StatusCode::operator[](int const &status_code)
{
	return _status_codes[status_code];
}

std::string
StatusCode::get_key_value_formated(int code) const
{
	std::string code_str;
	code_str = std98::to_string(code);
	return code_str + " " + _status_codes.at(code);
}

} /* namespace http */
