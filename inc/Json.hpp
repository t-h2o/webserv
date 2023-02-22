#ifndef JSON_HPP
#define JSON_HPP

#include <fstream>
#include <iostream>

class Json
{
  public:
	static void read(std::string const &);

  private:
	static void _process_line(std::string const &line);
};

#endif /* JSON_HPP */
