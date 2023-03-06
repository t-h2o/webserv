#include "Test.hpp"
#include <stdlib.h>

Test::Test(std::string const &name, int (*function_ptr)(void)) : _name(name), _function_ptr(function_ptr) {}

void
Test::do_test(void)
{
	_result.set_result(_function_ptr());
}
