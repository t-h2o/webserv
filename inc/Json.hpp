#ifndef JSON_HPP
#define JSON_HPP

#include <fstream>
#include <iostream>

#include "Value.hpp"

class Json
{
  public:
	static void read(std::string const &);

  private:
	static void		   _process_line(std::string const &line);
	static void		   _loop_isblank(std::string const &line, size_t &index);
	static std::string _get_string(std::string const &line, size_t &index);
};

#endif /* JSON_HPP */
