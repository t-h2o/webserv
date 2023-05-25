#ifndef STATUSCODE_HPP
#define STATUSCODE_HPP

#include "std98.hpp"
#include <iostream>
#include <map>
#include <sstream>
#include <string>

namespace http
{

class StatusCode
{
  private:
	std::map<int, std::string> _status_codes;

  public:
	StatusCode();
	std::string &operator[](int const &status_code);
	std::string	 get_key_value_formated(int code) const;
};

} /* namespace http */

#endif
