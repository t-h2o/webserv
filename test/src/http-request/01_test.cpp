#include "Stream.hpp"

#include "request.hpp"

int
test_http_request(void)
{
	http::Request request;

	char buff[] = "GET /website/favicon.ico HTTP/1.1\r\n"
				  "Host: localhost:8080\r\n"
				  "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:107.0) Gecko/20100101 "
				  "Firefox/107.0\r\n"
				  "Accept: image/avif,image/webp,/\r\n"
				  "Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3\r\n"
				  "Accept-Encoding: gzip, deflate, br\r\n"
				  "DNT: 1\r\n"
				  "Connection: keep-alive\r\n"
				  "Referer: http://localhost:8080/website/index.html\r\n"
				  "Sec-Fetch-Dest: image\r\n"
				  "Sec-Fetch-Mode: no-cors\r\n"
				  "Sec-Fetch-Site: same-origin\r\n"
				  ""
				  "navigate\r\n"
				  "Sec-Fetch-Site: none\r\n"
				  "Sec-Fetch-User: ?1\r\n";

	request.parse_buffer(buff);

	if (request.get_method() != "GET")
		return 1;

	if (request.get_path() != "/website/favicon.ico")
		return 1;

	if (request.get_host() != "localhost:8080")
		return 1;

	if (request.get_protocol() != "HTTP/1.1")
		return 1;

	if (request.get_protocol() != "HTTP/1.1")
		return 1;

	if (request.method_is_authorized("GET") != true)
		return 1;

	return 0;
}
