#ifndef VALUE_HPP
#define VALUE_HPP

#include <iostream>
#include <map>
#include <vector>

#include "Type.hpp"

class Value
{
  public:
	/* constructor */
	Value(void);
	Value(std::string *);
	Value(bool *);
	Value(double *);
	Value(std::vector<double> *);
	Value(std::map<std::string, Value> *);
	Value(Value const &);

	/* destructor */
	~Value();

	/* operator */
	Value &operator=(Value const &);
	double operator[](size_t const &);

	/* getter */
	size_t					 size(void) const;
	template <typename T> T &get(void) const;
	template <typename T> T &get(std::string const &) const;
	int						 get_type(void) const;

  private:
	void *_value;
	int	  _type;
};

/* extra */
std::ostream &operator<<(std::ostream &, Value const &);

#endif /* VALUE_HPP */
