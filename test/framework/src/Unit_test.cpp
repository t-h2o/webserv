#include "Unit_test.hpp"
#include <algorithm>

Unit_test::Unit_test(std::string const &name) : unit_name(name) {}

void
Unit_test::load_test(std::string const name, int (*function_test)(void))
{
	Test test(name, function_test);
	_test.push_back(test);
}

static void
do_test(Test &test)
{
	test.do_test();
}

void
Unit_test::_last_line(void)
{
	int success;

	success = 0;
	size_t index = _test.size();
	while (index-- && (_test[index]._result.failed() || ++success))
		;
	std::cout << "\n";
	std::cout << success;
	std::cout << "/";
	std::cout << _test.size();
	std::cout << " tests checked\n";
}

int
Unit_test::launch_tests(void)
{
	std::for_each(_test.begin(), _test.end(), do_test);

	std::vector<Test>::iterator it(_test.begin());
	std::vector<Test>::iterator it_end(_test.end());
	while (it != it_end)
	{
		std::cout << unit_name << " : " << it->_name << " : ";
		it++->_result.print_result();
	}
	_last_line();
	return (0);
}
