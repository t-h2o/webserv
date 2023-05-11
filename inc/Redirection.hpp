#ifndef REDIRECTION_HPP
#define REDIRECTION_HPP

#include "Json.hpp"

#define LOG_REDIRECTION false

namespace http
{

class Redirection
{
  public:
	Redirection(json::t_object const &);
	~Redirection();

	/* if it's a rediction, return true else false
	 * arguments:
	 * - 1: the root
	 * - 2: URL of the rediction, set in the function
	 */
	bool is_redirection(std::string const &, std::string &);

  private:
	json::t_object const &_redirections;
};

}; /* namespace http */

#endif
