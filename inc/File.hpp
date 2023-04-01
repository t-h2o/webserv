#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <iostream>
#include <stdexcept>

/* This class open a file at the construction of an instance
 * and close it at the desctruction.
 *
 * The get_next_char() member function return a character.
 * get_next_char() do not return any blank character.
 */

namespace json
{

class File
{
  public:
	File(const char *);
	~File(void);

	char get_next_char(void);

  private:
	std::string	 _current_line;
	std::fstream _file;
	size_t		 _index;

	void ignore_blank(void);
};

} /* namespace json */

#endif /* FILE_HPP */
