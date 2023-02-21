#ifndef RESULT_HPP
#define RESULT_HPP

#include <iostream>

class Result
{
  public:
	/* enumation result */
	enum e_result
	{
		OK,
		KO,
		sigsegv,
		sigbus,
		sigabrt,
		sigfpe,
		sigpip,
		sigill,
		unknown = -1
	};
	typedef enum e_result t_result;

	void print_result(void) const;
	void set_result(int);
	bool failed(void) const;

  private:
	t_result _result;
};

#endif /* RESULT_HPP */
