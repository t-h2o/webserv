#ifndef UTILS_JSON_HPP
#define UTILS_JSON_HPP

/* Utils header for Json.hpp */

#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <string.h>

#include "File.hpp"
#include "Json.hpp"

#define NSTATES 8

#define OBJECT 0
#define STRING 1
#define KEY_FILLED 2
#define MIDDLE 3
#define RIGHT 4
#define VALUE_FILLED 5
#define END 6		 /* ',' character */
#define END_OBJECT 7 /* ',' character */

#define LOG false

namespace json
{

t_object   *read(char const *);
void		_process_line(t_object *, File &, bool states[NSTATES]);
std::string _get_string(std::string const &line, size_t &index);
int			check_config(t_object *config);

} /* namespace json */

#endif /* UTILS_JSON_HPP */
