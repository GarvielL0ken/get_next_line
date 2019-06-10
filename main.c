#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "project_file/get_next_line.c"

int	main(int argc, char *argv[])
{
	int		fd;
	char	*str_1;
	char	*str_2;
	char	*str_3;
	int		ret_1;
	int		ret_2;
	int		ret_3;

	if (argc == 2)
	{
		fd = open(argv[1], 'r');
	
		ret_1 = get_next_line(-99, ((void *)0));
		//ret_2 = get_next_line(fd, &str_2);
		//ret_3 = get_next_line(fd, &str_3);
		printf("result: \n");
		printf("String 1: %s\nret = %d\n", str_1, ret_1);
		//printf("String 2: %s\nret = %d\n", str_2, ret_2);
		//printf("String 3: %s\nret = %d\n", str_3, ret_3);
	//printf("%s", str_1);
	//printf("%s", str_2);
	//printf("%s", str_3);
	}
}
