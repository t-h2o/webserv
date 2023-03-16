#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <iostream>
#include <stdexcept>

/* This class open a file at the construction of an instance
 * and close it at the desctruction.
 *
 * The getc() member function return a character.
 * getc() do not return any blank character.
 */

class File
{
  public:
	File(const char *);
	~File(void);

	char getc(void);

  private:
	std::string	 _current_line;
	std::fstream _file;
	size_t		 _index;

	void ignore_blank(void);
};

#endif /* FILE_HPP */
