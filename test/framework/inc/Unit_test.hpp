#ifndef UNIT_TEST_HPP
#define UNIT_TEST_HPP

#include <iostream>
#include <vector>

#include "Test.hpp"

/* structure unit_test */
class Unit_test
{
  private:
	std::vector<Test> _test;

  public:
	Unit_test(std::string const &);
	std::string unit_name;

	void load_test(std::string const, int (*)(void));
	int	 launch_tests(void);
	void _last_line(void);
};

#endif /* UNIT_TEST_HPP */
