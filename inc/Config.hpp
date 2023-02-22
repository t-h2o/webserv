#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>

#include "Value.hpp"

class Config
{
	typedef std::pair<std::string, Value *> t_pair;

  public:
	void insert_key(std::string const &);
	void insert_value(Value *);

  private:
	std::map<std::string, Value *> _config;
	std::string					   _last_key;
};

#endif /* CONFIG_HPP */
