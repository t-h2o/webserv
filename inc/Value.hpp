#ifndef VALUE_HPP
#define VALUE_HPP

#include <iostream>

#define V_STRING 1
#define V_NUMBER 2

class Value
{
  public:
	Value(std::string const &);
	Value(double const &);
	Value(Value const &);
	~Value();

	Value &operator=(Value const &);

	template <typename T> T get(void) const;

	int get_type(void) const;

  private:
	void *_value;
	int	  _type;
};

std::ostream &operator<<(std::ostream &, Value const &);

#endif /* VALUE_HPP */
