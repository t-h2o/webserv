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
	size_t size(void) const;
	enum e_type	   get_type(void) const;

	/* templates functions */
	template <typename T> T &get(void) const;
	template <typename T> T &get(std::string const &) const;

  private:
	void *_value;
	enum e_type	  _type;
};

#include "../templates/Value.cpp"

/* extra */
std::ostream &operator<<(std::ostream &, Value const &);

#endif /* VALUE_HPP */
