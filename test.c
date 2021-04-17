#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "get_next_line.h"

int main(int ac, char **av)
{
	int fd;
	int c = 1;
	char *line = NULL;
	char *map;

	fd = open(av[1], O_RDONLY);
	while (c != 0)
	{
		c = get_next_line(fd, &line);
		printf("%s\n", line);
	}
	return (0);
}
