#include "Stream.hpp"

#include "httpRequest.hpp"

int
test_http_request(void)
{
	HttpRequest request;

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

	request.parseBuffer(buff);

	if (request.getMethod() != "GET")
		return 1;

	if (request.getPath() != "/website/favicon.ico")
		return 1;

	if (request.getHost() != "localhost:8080")
		return 1;

	if (request.getProtocol() != "HTTP/1.1")
		return 1;

	if (request.getProtocol() != "HTTP/1.1")
		return 1;

	if (request.methodIsAuthorized("GET") != true)
		return 1;

	return 0;
}
