#ifndef UTILS_JSON_HPP
#define UTILS_JSON_HPP

/* Utils header for Json.hpp */

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string.h>

#include "Json.hpp"
#include "Value.hpp"

#define NSTATES 7

#define OBJECT 0
#define STRING 1
#define KEY_FILLED 2
#define MIDDLE 3
#define RIGHT 4
#define VALUE_FILLED 5
#define END 6 /* ',' character */

#define LOG false

void		_ignore_blank(std::string const &, size_t &);
void		_process_line(Config *, std::string const &line, bool states[NSTATES]);
std::string _get_string(std::string const &line, size_t &index);

#endif /* UTILS_JSON_HPP */
