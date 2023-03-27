#include <iostream>
using namespace std;

int
main()
{
	string str1 = "Hello from ";

	cout << "String without appending: " << str1 << endl;
	str1.append("Educative!!!", 9);

	cout << "String after appending: " << str1;

	return 0;
}