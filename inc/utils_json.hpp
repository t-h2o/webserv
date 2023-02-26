#ifndef UTILS_JSON_HPP
#define UTILS_JSON_HPP

/* Utils header for Json.hpp */

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string.h>

#include "Json.hpp"
#include "Value.hpp"

#define NSTATES 3

void		_process_line(Config *, std::string const &line, bool states[NSTATES]);
void		_loop_isblank(std::string const &line, size_t &index);
std::string _get_string(std::string const &line, size_t &index);

#endif /* UTILS_JSON_HPP */
