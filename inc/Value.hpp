#ifndef VALUE_HPP
#define VALUE_HPP

#include <iostream>
#include <vector>

#include "Type.hpp"

class Value
{
  public:
	Value(void);
	Value(std::string *);
	Value(bool *);
	Value(double *);
	Value(std::vector<double> *);
	Value(Value const &);
	~Value();

	Value &operator=(Value const &);
	double operator[](size_t const &);

	size_t size(void) const;

	template <typename T> T & get(void) const;

	int get_type(void) const;

  private:
	void *_value;
	int	  _type;
};

std::ostream &operator<<(std::ostream &, Value const &);

#endif /* VALUE_HPP */
