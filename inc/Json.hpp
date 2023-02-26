#ifndef JSON_HPP
#define JSON_HPP

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string.h>

#include "Config.hpp"
#include "Value.hpp"

#define NSTATES 4

Config *read(char const *);

void		_process_line(Config *, std::string const &line, bool states[NSTATES]);
void		_loop_isblank(std::string const &line, size_t &index);
std::string _get_string(std::string const &line, size_t &index);

#endif /* JSON_HPP */
