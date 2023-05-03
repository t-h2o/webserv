#include "StatusCodes.hpp"

#include "../../../inc/cgi.hpp"
#include "../../../inc/Response.hpp"

std::map<std::string, std::string>
request(void)
{
	std::map<std::string, std::string> map;
	char array[] = "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\n"
					"Accept-Encoding: gzip, deflate, br\n"
					"Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;\n"
					"q=0.3 Connection: keep-alive\n"
					"Content-Type:\n"
					"Cookie: wp-settings-time-1=1677339113\n"
					"Host: localhost:6060\n"
					"Method: GET\n"
					"Path: /input.php\n"
					"Protocol: HTTP/1.1\n"
					"Query: name=kevin\n"
					"Sec-Fetch-Dest: document\n"
					"Sec-Fetch-Mode: navigate\n"
					"Sec-Fetch-Site: none\n"
					"Upgrade-Insecure-Requests: 1\n"
					"User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:107.0) Gecko/20100101 Firefox/107.0\n";
	std::stringstream ss(array);
	std::string line;
	while (std::getline(ss, line))
	{
		size_t s_count = line.find(": ");
		if (s_count != std::string::npos)
		{
			std::string key = line.substr(0,s_count);
			std::string value = line.substr(s_count + 2);
			map.insert(std::make_pair(key, value));
		}
	}
	return (map);
}

int
test_php_output(void)
{
	http::Response	pp;
	std::map<std::string, std::string> map;
	std::string		str;
	std::cout << "php test no problemo!" << std::endl;

	map = request();
	std::map<std::string, std::string>::iterator it;
	for (it = map.begin(); it != map.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;
	return (0);
}
