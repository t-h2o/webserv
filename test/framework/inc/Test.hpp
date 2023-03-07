#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

#include "Result.hpp"

class Test
{
  public:
	Test(std::string const &, int (*)(void));

	std::string _name;
	int (*_function_ptr)(void);
	Result _result;

	void do_test(void);
};

#endif /* TEST_HPP */
