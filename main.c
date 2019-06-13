#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "project_file/get_next_line.c"

int	main(int argc, char *argv[])
{
	int		fd;
	int		len = 50;
	char	*str_1;
	char	*str_2;
	char	*str_3;
	char	*str_4;
	int		ret_1;
	int		ret_2;
	int		ret_3;

	if (argc == 2)
	{
		fd = open(argv[1], 'r');
	
		ret_1 = get_next_line(fd, &str_1);
		ret_2 = get_next_line(fd, &str_2);
		ret_3 = get_next_line(fd, &str_3);
		printf("result: \n");
		printf("String 1: %s\nret = %d\n", str_1, ret_1);
		printf("String 2: %s\nret = %d\n", str_2, ret_2);
		printf("String 3: %s\nret = %d\n", str_3, ret_3);

		if (ft_strcmp(argv[1], "test_40") == 0)
		{
			str_4 = (char *)malloc(1000 * 1000);
			*str_4 = '\0';
			ft_strcat(str_4, "Lo\n");
			printf("String 4: %s\n", str_4);
			printf("ft_strcmp(str_1, str_4) = %d\n", ft_strcmp(str_1, str_4));
		}
	}
	else if (argc == 3)
	{
		str_1 = (char *)malloc(1000 * 1000);
		*str_1 = '\0';
		ft_strcat(str_1, "Lo\n");
		fd = open(argv[1], O_RDWR);
		if (str_1)
			write(fd, str_1, ft_strlen(str_1));
	}
}
