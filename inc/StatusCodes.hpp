#ifndef STATUSCODE_HPP
#define STATUSCODE_HPP

#include <iostream>
#include <map>
#include <string>
#include <sstream>

namespace http
{

class StatusCode
{
  private:
	std::map<int, std::string> _status_codes;

  public:
	StatusCode();
	std::string &operator[](int status_code);
	std::string	 get_key_value_formated(int code) const;
};

} /* namespace http */

#endif
