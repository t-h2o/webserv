#include "File.hpp"

File::File(const char *path_file) : _index(0)
{
	_file.open(path_file, std::fstream::in);

	/* Check if the file is valid */
	if (_file.is_open() == 0)
		throw std::runtime_error("Error: read(): file is not valid");

	getline(_file, _current_line);
}

File::~File(void) { _file.close(); }

char
File::getc(void)
{
	if (_current_line[_index] == 0)
	{
		if (_file.eof())
			return 0;

		getline(_file, _current_line);
		_index = 0;
		return getc();
	}

	return _current_line[_index++];
}
