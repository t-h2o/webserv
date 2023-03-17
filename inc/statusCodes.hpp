#ifndef STATUSCODE_HPP
#define STATUSCODE_HPP

#include <iostream>
#include <map>
#include <string>

namespace http
{

class StatusCode
{
  private:
	std::map<std::string, std::string> _status_codes;

  public:
	StatusCode();
	std::string &operator[](std::string status_code);
	std::string	 get_key_value_formated(int code) const;
};

} /* namespace http */

#endif