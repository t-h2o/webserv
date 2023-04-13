#include <iostream>
#include <stdexcept>
#include <string>

void
my_function()
{
	int i = rand();
	// Vérifier si une erreur s'est produite
	if (i != 2)
		throw std::runtime_error("Une erreur s'est produite dans my_function()");
	// Lancer une exception avec une description de l'erreur
	else
		std::cout << i << " value is correct" << std::endl;
}

int
main()
{
	try
	{
		my_function();
	}
	catch (std::runtime_error &e)
	{
		// Afficher la description de l'erreur
		std::string message = e.what();
		std::cout << message << std::endl;
	}

	return 0;
}
