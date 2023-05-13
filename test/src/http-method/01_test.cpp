#include "Method.hpp"

int
test_http_method(void)
{
	// true is allowed
	// false isn't allowed
	// GET    : 1 3 5 7
	// POST   : 2 3 6 7
	// DELETE : 4 5 6 7

	json::t_object method_allowed;

	method_allowed["/"] = json::Value(new double(2));
	method_allowed["/path"] = json::Value(new double(2));
	method_allowed["/file"] = json::Value(new double(2));

	http::Method method(method_allowed);

	/* get is not allow */

	if (method.is_allowed("/path", "GET") != 0)
	{
		std::cerr << "1.1: failed" << std::endl;
		return 1;
	}

	if (method.is_allowed("/path/file", "GET") != 0)
	{
		std::cerr << "1.2: failed" << std::endl;
		return 1;
	}

	if (method.is_allowed("/file", "GET") != 0)
	{
		std::cerr << "1.3: failed" << std::endl;
		return 1;
	}

	/* post is allow */

	if (method.is_allowed("/path", "POST") == 0)
	{
		std::cerr << "1.4: failed" << std::endl;
		return 1;
	}

	if (method.is_allowed("/path/file", "POST") == 0)
	{
		std::cerr << "1.5: failed" << std::endl;
		return 1;
	}

	if (method.is_allowed("/file", "POST") == 0)
	{
		std::cerr << "1.6: failed" << std::endl;
		return 1;
	}

	/* delete is not allow */

	if (method.is_allowed("/path", "DELETE") != 0)
	{
		std::cerr << "1.7: failed" << std::endl;
		return 1;
	}

	if (method.is_allowed("/path/file", "DELETE") != 0)
	{
		std::cerr << "1.8: failed" << std::endl;
		return 1;
	}

	if (method.is_allowed("/file", "DELETE") != 0)
	{
		std::cerr << "1.9: failed" << std::endl;
		return 1;
	}

	return 0;
}
