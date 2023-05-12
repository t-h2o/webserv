#include "Method.hpp"

#define ALL_RIGHT 7
namespace http
{

Method::Method(json::t_object const &method_allowed) : _method_allowed(method_allowed)
{

	if (LOG_METHOD)
		std::cout << "http::Method: method_allowed: " << _method_allowed << std::endl;
}
Method::~Method() {}

/*
 * case 1: path file is more far than the key
 * path_file : /path/to/file
 * key       : /path/to/
 *
 * the path_file heritance the key protection
 *
 *
 * case 2: path file is less far than the key
 * path_file : /path/to/
 * key       : /path/to/file
 *
 * by default all website is available by all http method,
 * so if there is no case 1, the path_file is allowed
 *
 *
 * case 3: path is identical to the key
 * path_file : /path/to/file
 * key       : /path/to/file
 *
 * as the case 1
 */
/* the purpose of bigger_size_key is to take the much path specialize as possible
 * perhaps it's overkill due the map is already sorted
 */
unsigned char
Method::get_value(std::string const &path_file)
{
	size_t		  bigger_size_key(0);
	unsigned char value(ALL_RIGHT);

	for (json::t_object::const_iterator it(_method_allowed.begin()); it != _method_allowed.end(); ++it)
	{
		size_t size_key(it->first.size());

		if (it->first.compare(0, size_key, path_file, 0, size_key) == 0)
		{
			if (!bigger_size_key || bigger_size_key < size_key)
			{
				bigger_size_key = size_key;
				value = it->second.get<double>();
			}
		}
	}
	return value;
}

/*
 * GET    -> 1 : 1   3   5   7
 * POST   -> 2 :   2 3     6 7
 * DELETE -> 4 :       4 5 6 7
 *
 * example:
 * for a value of 1 and method "GET"
 * this function return true.
 *
 * for a value of 2 and method "GET"
 * this function return false.
 *
 * for a value of 3 and method "GET"
 * this function return true.
 *
 * for a value of 3 and method "POST"
 * this function return true.
 *
 * for a value of 4 and method "POST"
 * this function return false.
 *
 * for a value of 5 and method "POST"
 * this function return false.
 */
bool
Method::permission_method_converter(const unsigned int permission, std::string const &method)
{
	// over-range
	if (7 < permission)
		return true;

	// GET    : 1 3 5 7
	if (!method.compare("GET"))
		return permission % 2;

	// POST   : 2 3 6 7
	if (!method.compare("POST"))
		return 1 < permission % 4;

	// DELETE : 4 5 6 7
	if (!method.compare("DELETE"))
		return 3 < permission;

	return false;
}

bool
Method::is_allowed(std::string const &path_file, std::string const &http_method)
{
	unsigned int permission(get_value(path_file));

	if (LOG_METHOD)
		std::cout << "http::Method:  file path: " << path_file << std::endl;

	if (LOG_METHOD)
		std::cout << "http::Method: permission: " << permission << std::endl;

	bool method_allowed(permission_method_converter(permission, http_method));

	if (LOG_METHOD)
		std::cout << "http::Method: allowed   : " << method_allowed << std::endl;

	return method_allowed;
}

} /* namespace http */
