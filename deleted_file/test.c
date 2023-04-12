#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	sleep(10);
	char *vi = (char *) malloc(sizeof(char *) * strlen(av[1]));
	for (int i = 0; i != 1000; ++i);

	vi = (char *) malloc(sizeof(char *) * strlen(av[1]));
	return (0);	
}
