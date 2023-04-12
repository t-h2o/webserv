//
// Created by Kevin Di nocera on 4/5/23.
//
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

int
main()
{
	//	const char* array[] = {"hello", "world"};
	//	int size = sizeof(array) / sizeof(array[0]);
	//	std::cout << "Taille du tableau : " << size << std::endl;
	std::map<std::string, std::string> myMap;
	myMap.insert(std::make_pair("key1", "value1"));
	myMap.insert(std::make_pair("key2", "value2"));
	myMap.insert(std::make_pair("key3", "value3"));

	// Allocation de l'espace mémoire
	char **array = new char *[myMap.size() + 1];
	int	   i = 0;
	// Concaténation des chaînes
	for (std::map<std::string, std::string>::iterator it = myMap.begin(); it != myMap.end(); ++it)
	{
		array[i] = new char[it->first.size() + it->first.size() + 3];
		std::string tmps = it->first + " = " + it->second;
		strcpy(array[i], tmps.c_str());
		i++;
	}
	array[i] = NULL;

	// Affichage du résultat
	for (int j = 0; array[j]; j++)
		std::cout << array[j] << std::endl;

	// Libération de la mémoire
	for (int j = 0; array[j]; j++)
		delete[] array[j];

	return 0;
	//	char** array = new char*[myMap.size() + 1];
	//
	//	int i = 0;
	//	for (std::map<const char*, const char*>::const_iterator it = myMap.begin(); it != myMap.end(); ++it) {
	//		char* tmp = new char[std::strlen(it->first) + std::strlen(it->second) + 4];
	//		std::sprintf(tmp, "%s = %s", it->first, it->second);
	//		array[i++] = tmp;
	//	}
	//	array[i] = NULL;
	//	for (int j = 0; array[j]; j++)
	//		std::cout << array[j] << std::endl;

	return 0;
}