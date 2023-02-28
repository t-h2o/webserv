#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <algorithm>
#include <map>

#include "Value.hpp"

class Config
{
	typedef std::pair<std::string, Value *> t_pair;

  public:
	~Config(void);

	void insert_pair(t_pair const &);
	void print_all(void) const;

	template <typename T>
	T
	get(std::string const &key)
	{
		std::map<std::string, Value *>::iterator it(_config.find(key));
		if (it == _config.end())
			throw std::exception();
		return it->second->get<T>();
	}

  private:
	std::map<std::string, Value *> _config;
	std::string					   _last_key;

	static void _print_pair(t_pair);
	void		_free_values();
	static void _delete_value(t_pair);
};

#endif /* CONFIG_HPP */
