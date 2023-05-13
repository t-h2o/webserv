#include "Redirection.hpp"

#define GOOGLE	"google.com"
#define DUCK	"duckduckgo.com"

int
test_http_redirection(void)
{
	json::t_object redirections;

	redirections["/site_sheep"] = json::Value(new std::string(GOOGLE));
	redirections["/site_duck"] = json::Value(new std::string(DUCK));

	http::Redirection redirection(redirections);

	std::string url;

	if (!redirection.is_redirection("/site_sheep", url))
	{
		std::cerr << "http::Redirection: error: \"/site_sheep\"" << std::endl;
		return 1;
	}
	if (url.compare(GOOGLE))
	{
		std::cerr << "http::Redirection: error: \"/site_sheep\"" << std::endl;
		return 1;
	}

	if (!redirection.is_redirection("/site_duck", url))
	{
		std::cerr << "http::Redirection: error: \"/site_duck\"" << std::endl;
		return 1;
	}
	if (url.compare(DUCK))
	{
		std::cerr << "http::Redirection: error: \"/site_duck\"" << std::endl;
		return 1;
	}

	if (redirection.is_redirection("/no-redirection", url))
	{
		std::cerr << "http::Redirection: error: \"/no-redirection\"" << std::endl;
		return 1;
	}

	return 0;
}
