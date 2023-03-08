#ifndef STREAM_HPP
#define STREAM_HPP

#include <iostream>
#include <sstream>
#include <streambuf>

class Stream
{
  public:
	void open(void);
	void close(void);

	std::string get_cout(void) const;
	std::string get_cerr(void) const;

	int check(std::string const &, std::string const &);

  private:
	std::stringstream _ss_out;
	std::stringstream _ss_err;
	std::streambuf	 *_sb_fout;
	std::streambuf	 *_sb_ferr;
	std::streambuf	 *_sb_cout;
	std::streambuf	 *_sb_cerr;
};

#endif /* STREAM_HPP */
