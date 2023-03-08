#include "Stream.hpp"

void
Stream::open(void)
{
	/* backup of stream buffer */
	_sb_cout = std::cout.rdbuf();
	_sb_cerr = std::cout.rdbuf();

	/* get the stream buffer of the string stream */
	_sb_fout = _ss_out.rdbuf();
	_sb_ferr = _ss_err.rdbuf();

	/* change the stream buffer */
	std::cout.rdbuf(_sb_fout);
	std::cerr.rdbuf(_sb_ferr);
}

void
Stream::close(void)
{
	/* set the cout stream buffer */
	std::cout.rdbuf(_sb_cout);
	std::cerr.rdbuf(_sb_cerr);
}

std::string
Stream::get_cout(void) const
{
	return _ss_out.str();
}

std::string
Stream::get_cerr(void) const
{
	return _ss_err.str();
}

int
Stream::check(std::string const &out, std::string const &err)
{
	if (get_cout() == out && get_cerr() == err)
		return 0;
	return 1;
}
