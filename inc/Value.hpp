#ifndef VALUE_HPP
#define VALUE_HPP

#include <iostream>
#include <map>
#include <vector>

#include "type.hpp"

#define LOG_JSON_VALUE false

namespace json
{

class Value
{
  public:
	/* constructor */
	Value(void);
	Value(std::string *);
	Value(bool *);
	Value(double *);
	Value(t_array *);
	Value(t_object *);
	Value(Value const &);

	/* destructor */
	~Value();
	void delete_value();

	/* operator */
	Value &operator=(Value const &);
	Value &operator[](size_t const &);

	/* getter */
	size_t		size(void) const;
	enum e_type get_type(void) const;
	Value	   &get(std::string const &) const;
	bool		if_exist(std::string const &key) const;

	void duplicate(t_object const &);

	/* templates functions */
	template <typename T> T &get(void) const;

  private:
	void	   *_value;
	enum e_type _type;
};

#include "../templates/Value.cpp"

/* extra */
std::ostream &operator<<(std::ostream &, json::t_array const &);
std::ostream &operator<<(std::ostream &, json::t_object const &);
std::ostream &operator<<(std::ostream &, Value const &);

} /* namespace json */

#endif /* VALUE_HPP */
