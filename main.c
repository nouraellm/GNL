#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    int		fd;
    char	*line;

    int r1 = 1;
    int i = 1;

    while (i <= argc)
    {
	fd = open(argv[i], O_RDONLY);
	while ((r1 = get_next_line(fd, &line)) > 0)
       	{
		printf("%s\n",line);
		free(line);
       	}
      	i++;
    }
    return (0);
}
