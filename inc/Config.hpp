#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <algorithm>
#include <map>

#include "Value.hpp"

class Config
{
	typedef std::pair<std::string, Value> t_pair;

  public:
	void insert_pair(t_pair const &);
	void print_all(void) const;

	template <typename T> T get(std::string const &key);

  private:
	std::map<std::string, Value> _config;
	std::string					 _last_key;

	static void _print_pair(t_pair);
};

#include "../templates/Config.cpp"

#endif /* CONFIG_HPP */
