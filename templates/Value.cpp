/* getter */

template <typename T>
T &
Value::get(void) const
{
	return *static_cast<T *>(_value);
}
