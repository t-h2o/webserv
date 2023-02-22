#ifndef JSON_HPP
#define JSON_HPP

#include <fstream>
#include <iostream>

#include "Config.hpp"
#include "Value.hpp"

class Json
{
  public:
	static Config *read(std::string const &);

  private:
	static void		   _process_line(Config *, std::string const &line);
	static void		   _loop_isblank(std::string const &line, size_t &index);
	static std::string _get_string(std::string const &line, size_t &index);
};

#endif /* JSON_HPP */
