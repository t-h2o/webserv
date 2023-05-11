#ifndef METHOD_HPP
#define METHOD_HPP

#include "Json.hpp"

#define LOG_METHOD false

namespace http
{

class Method
{
  public:
	Method(json::t_object const &);
	~Method();

	bool is_allowed(std::string const &, std::string const &);

  private:
	json::t_object const &_method_allowed;

	unsigned char get_value(std::string const &);
	bool		  permission_method_converter(unsigned int const, std::string const &);
};

}; /* namespace http */

#endif
