#ifndef VALUE_HPP
#define VALUE_HPP

#include <iostream>
#include <vector>

#define V_STRING 1
#define V_NUMBER 2
#define V_VEC_NUMBER 3

class Value
{
  public:
	Value(void);
	Value(std::string const &);
	Value(double const &);
	Value(std::vector<double> *);
	Value(Value const &);
	~Value();

	Value &operator=(Value const &);
	double operator[](size_t const &);

	size_t size(void) const;

	template <typename T> T get(void) const;

	int get_type(void) const;

  private:
	void *_value;
	int	  _type;
};

std::ostream &operator<<(std::ostream &, Value const &);

#endif /* VALUE_HPP */
