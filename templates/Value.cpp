/* getter */

template <typename T>
T &
Value::get(void) const
{
	return *static_cast<T *>(_value);
}

/* Search the key into the map for returning the value */
template <typename T>
T &
Value::get(std::string const &key) const
{
	return get<std::map<std::string, Value> >().find(key)->second.get<T>();
}
