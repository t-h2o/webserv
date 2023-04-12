//
// Created by Kevin Di nocera on 3/27/23.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	setenv("REQUEST_METHOD", "5", 1);
	char *request_method = getenv("REQUEST_METHOD");
	if (request_method != NULL)
	{
		std::cout << "REQUEST_METHOD: " << request_method << std::endl;
	}
	else
	{
		std::cout << "REQUEST_METHOD not found" << std::endl;
	}

	return 0;
}
