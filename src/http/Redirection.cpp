#include "Redirection.hpp"

namespace http
{

Redirection::Redirection(json::t_object const &redirections) : _redirections(redirections)
{

	if (LOG_REDIRECTION)
		std::cout << "http::Redirection: constructor: redirection: " << _redirections << std::endl;
}

Redirection::~Redirection() {}

bool
Redirection::is_redirection(std::string const &route, std::string &url)
{
	json::t_object::const_iterator redirection = _redirections.find(route);

	if (redirection == _redirections.end())
	{
		if (LOG_REDIRECTION)
			std::cout << "http::Redirection: it isn't a redirection" << std::endl;
		return false;
	}

	if (LOG_REDIRECTION)
		std::cout << "http::Redirection: it is a redirection" << std::endl;

	url = redirection->second.get<std::string>();

	return true;
}

} /* namespace http */
