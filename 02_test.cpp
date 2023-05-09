//
// Created by Kevin Di nocera on 5/8/23.
//
// #include "StatusCodes.hpp"
//
// #include "../../../inc/cgi.hpp"
// #include "../../../inc/Response.hpp"
//
//
// std::map<std::string, std::string>
// request_POST(void)
//{
//	std::map<std::string, std::string> map;
//	char array[] = "Accept:
//text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\n" 												 "Accept-Encoding:
//gzip, deflate, br\n" 												 "Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;\n" 												 "q=0.3 Connection: keep-alive\n"
//												 "Content-Type:\n"
//												 "Content-Length: 19\n"
//												 "Cookie: wp-settings-time-1=1677339113\n"
//												 "Host: localhost:6060\n"
//												 "Method: POST\n"
//												 "Path: /input.php\n"
//												 "Protocol: HTTP/1.1\n"
//												 "Query:\n"
//												 "Sec-Fetch-Dest: document\n"
//												 "Sec-Fetch-Mode: navigate\n"
//												 "Sec-Fetch-Site: none\n"
//												 "Upgrade-Insecure-Requests: 1\n"
//												 "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:107.0) Gecko/20100101
//Firefox/107.0\n"; 	std::stringstream ss(array); 	std::string line; 	while (std::getline(ss, line))
//	{
//		size_t s_count = line.find(": ");
//		if (s_count != std::string::npos)
//		{
//			std::string key = line.substr(0,s_count);
//			std::string value = line.substr(s_count + 2);
//			map.insert(std::make_pair(key, value));
//		}
//	}
//	return (map);
//}
//
// int
// test_php_output(void)
//{
//	std::map<std::string, std::string> map;
//	std::string	str;
//	CGI	cgi;
//
//	map = request_POST();
//	if (map.empty())
//	{
//		std::cerr << "map is empty" << std::endl;
//		return (1);
//	}
//	//	std::map<std::string, std::string>::iterator it;
//	//	for (it = map.begin(); it != map.end(); ++it)
//	//		std::cout << it->first << " " << it->second << std::endl;
//	return (0);
//}