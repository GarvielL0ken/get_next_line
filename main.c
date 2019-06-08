#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_ver_3.c"

int	main()
{
	int		fd;
	char	*str_1;
	char	*str_2;
	char	*str_3;

	fd = open("test", 'r');
	str_1 = (char *)malloc(64);
	str_1[63] = '\0';
	str_2 = (char *)malloc(64);
	str_2[63] = '\0';
	str_3 = (char *)malloc(64);
	str_3[63] = '\0';

	get_next_line(fd, &str_1);
	get_next_line(fd, &str_2);
	get_next_line(fd, &str_3);
	printf("\nresult: \n");
	printf("String 1: %s\n", str_1);
	printf("String 2: %s\n", str_2);
	printf("String 3: %s\n", str_3);
	//printf("%s", str_1);
	//printf("%s", str_2);
	//printf("%s", str_3);
}