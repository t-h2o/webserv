#ifndef JSON_HPP
#define JSON_HPP

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string.h>

#include "Config.hpp"
#include "Value.hpp"

#define NSTATES 4

class Json
{
  public:
	static Config *read(char const *);

  private:
	static void		   _process_line(Config *, std::string const &line, bool states[NSTATES]);
	static void		   _loop_isblank(std::string const &line, size_t &index);
	static std::string _get_string(std::string const &line, size_t &index);
};

#endif /* JSON_HPP */
