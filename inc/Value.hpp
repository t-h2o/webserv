#ifndef VALUE_HPP
#define VALUE_HPP

#include <iostream>

class Value
{
  public:
	Value(std::string const &);

	std::string get(void) const;

  private:
	std::string _value;
};

std::ostream &operator<<(std::ostream &, Value const &);

#endif /* VALUE_HPP */
