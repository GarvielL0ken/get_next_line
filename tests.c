/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 13:20:24 by mcarter           #+#    #+#             */
/*   Updated: 2019/07/08 11:32:59 by jsarkis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"
#include <fcntl.h>
#include <string.h>
#define STR		char *
#define CYAN	"\e[36m"
#define BGREEN	"\e[1;32m"
#define BRED	"\e[1;31m"
#define RESET	"\e[0m"

# define mt_assert(x) debug(x, __func__)

void	debug(int pass, const STR caller_name)
{
	static int	lasttest;
	static int	testn;
	int			ctest;
	
	ctest = ft_atoi(caller_name + 4);
	if (ctest != lasttest)
	{
		ft_putchar('\n');
		lasttest = ctest;
		testn = 1;
	}
	ft_putstr(CYAN "[");
	ft_putstr(caller_name);
	ft_putchar('-');
	ft_putnbr(testn++);
	ft_putstr("]" RESET " ");
	if (pass)
		ft_putstr(BGREEN "pass " RESET);
	else
		ft_putstr(BRED "fail " RESET);
}

void test01(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;

	fd = 1;
	out = dup(fd);
	pipe(p);

	dup2(p[1], fd);
	write(fd, "aaa\nbbb\nccc\nddd\n", 16);
	dup2(out, fd);
	close(p[1]);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "aaa") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "bbb") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "ccc") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "ddd") == 0);
}

void test02(void)
{
	char *line;
	int		out;
	int		p[2];
	int		fd;
	int		gnl_ret;

	fd = 1;
	out = dup(fd);
	pipe(p);
	dup2(p[1], fd);
	write(fd, "aaa", 3);
	close(p[1]);
	dup2(out, fd);
	gnl_ret = get_next_line(p[0], &line);
	mt_assert(strcmp(line, "aaa") == 0);
	mt_assert(gnl_ret == 0 || gnl_ret == 1);
}

void test03(void)
{
	char 	*line;
	int		out;
	int		p[2];
	char 	*str;
	int		gnl_ret;

	str = (char *)malloc(1000 * 1000);
	*str = '\0';
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	out = dup(1);
	pipe(p);
	dup2(p[1], 1);

	write(1, str, strlen(str));
	close(p[1]);
	dup2(out, 1);
	gnl_ret = get_next_line(p[0], &line);
	mt_assert(strcmp(line, str) == 0);
	mt_assert(gnl_ret == 0 || gnl_ret == 1);
}

void test04(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		gnl_ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abc\n\n", 5);
	close(p[1]);
	dup2(out, fd);

	/* Read abc and new line */
	gnl_ret = get_next_line(p[0], &line);
	mt_assert(gnl_ret == 1);
	mt_assert(strcmp(line, "abc") == 0);

	/* Read new line */
	gnl_ret = get_next_line(p[0], &line);
	mt_assert(gnl_ret == 1);
	mt_assert(line == NULL || *line == '\0');

	/* Read again, but meet EOF */
	gnl_ret = get_next_line(p[0], &line);
	mt_assert(gnl_ret == 0);
	mt_assert(line == NULL || *line == '\0');

	/* Let's do it once again */
	gnl_ret = get_next_line(p[0], &line);
	mt_assert(gnl_ret == 0);
	mt_assert(line == NULL || *line == '\0');
}

void test05(void)
{
    char 	*line = NULL;
    
	mt_assert(get_next_line(-99, NULL) == -1);
	mt_assert(get_next_line(-1, NULL) == -1);
	mt_assert(get_next_line(-10000, NULL) == -1);
	mt_assert(get_next_line(1, NULL) == -1);
	mt_assert(get_next_line(99, NULL) == -1);

	mt_assert(get_next_line(-99, &line) == -1);
	mt_assert(get_next_line(-1, &line) == -1);
	mt_assert(get_next_line(-10000, &line) == -1);

	/* Not opened fd */
	mt_assert(get_next_line(42, &line) == -1);
}

void test06(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "oiuytrew\n", 9);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "oiuytrew") == 0);
}

void test07(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	
	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcdefgh\n", 9);
	write(fd, "ijklmnop\n", 9);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "abcdefgh") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "ijklmnop") == 0);
}

void test08(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcdefgh\n", 9);
	write(fd, "ijklmnop\n", 9);
	write(fd, "qrstuvwx\n", 9);
	write(fd, "yzabcdef\n", 9);
	write(fd, "ghijklmn\n", 9);
	write(fd, "opqrstuv\n", 9);
	write(fd, "wxyzabcd\n", 9);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "abcdefgh") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "ijklmnop") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "qrstuvwx") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "yzabcdef") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "ghijklmn") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "opqrstuv") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "wxyzabcd") == 0);
}

void test09(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcdefghijklmnop\n", 17);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "abcdefghijklmnop") == 0);
	ret = get_next_line(p[0], &line);
	mt_assert(ret == 0);
}

void test10(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcdefghijklmnop\n", 17);
	write(fd, "qrstuvwxyzabcdef\n", 17);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "abcdefghijklmnop") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "qrstuvwxyzabcdef") == 0);
	ret = get_next_line(p[0], &line);
	mt_assert(ret == 0);
}

void test11(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcdefghijklmnop\n", 17);
	write(fd, "qrstuvwxyzabcdef\n", 17);
	write(fd, "ghijklmnopqrstuv\n", 17);
	write(fd, "wxyzabcdefghijkl\n", 17);
	write(fd, "mnopqrstuvwxyzab\n", 17);
	write(fd, "cdefghijklmnopqr\n", 17);
	write(fd, "stuvwxzabcdefghi\n", 17);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "abcdefghijklmnop") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "qrstuvwxyzabcdef") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "ghijklmnopqrstuv") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "wxyzabcdefghijkl") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "mnopqrstuvwxyzab") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "cdefghijklmnopqr") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "stuvwxzabcdefghi") == 0);
	ret = get_next_line(p[0], &line);
	mt_assert(ret == 0);
}

void test12(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcd\n", 5);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "abcd") == 0);
	ret = get_next_line(p[0], &line);
	mt_assert(ret == 0);
}

void test13(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcd\n", 5);
	write(fd, "efgh\n", 5);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "abcd") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "efgh") == 0);
	ret = get_next_line(p[0], &line);
	mt_assert(ret == 0);
}

void test14(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcd\n", 5);
	write(fd, "efgh\n", 5);
	write(fd, "ijkl\n", 5);
	write(fd, "mnop\n", 5);
	write(fd, "qrst\n", 5);
	write(fd, "uvwx\n", 5);
	write(fd, "yzab\n", 5);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "abcd") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "efgh") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "ijkl") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "mnop") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "qrst") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "uvwx") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "yzab") == 0);
	ret = get_next_line(p[0], &line);
	mt_assert(ret == 0);
}

void test15(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcd", 4);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "abcd") == 0);
}

void test16(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "efghijkl", 8);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "efghijkl") == 0);
}

void test17(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "mnopqrstuvwxyzab", 16);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "mnopqrstuvwxyzab") == 0);
}

void test30(void)
{
	char	*line_fd0;
	int		p_fd0[2];
	int		fd0 = 0;
	int		out_fd0 = dup(fd0);

	char	*line_fd1;
	int		p_fd1[2];
	int		fd1 = 1;
	int		out_fd1 = dup(fd1);

	char	*line_fd2;
	int		p_fd2[2];
	int		fd2 = 2;
	int		out_fd2 = dup(fd2);

	char	*line_fd3;
	int		p_fd3[2];
	int		fd3 = 3;
	int		out_fd3 = dup(fd3);

	pipe(p_fd0);
	dup2(p_fd0[1], fd0);
	write(fd0, "aaa\nbbb\n", 8);
	dup2(out_fd0, fd0);
	close(p_fd0[1]);

	pipe(p_fd1);
	dup2(p_fd1[1], fd1);
	write(fd1, "111\n222\n", 8);
	dup2(out_fd1, fd1);
	close(p_fd1[1]);

	pipe(p_fd2);
	dup2(p_fd2[1], fd2);
	write(fd2, "www\nzzz\n", 8);
	dup2(out_fd2, fd2);
	close(p_fd2[1]);

	pipe(p_fd3);
	dup2(p_fd3[1], fd3);
	write(fd3, "888\n999\n", 8);
	dup2(out_fd3, fd3);
	close(p_fd3[1]);

	get_next_line(p_fd0[0], &line_fd0);
	mt_assert(strcmp(line_fd0, "aaa") == 0);

	get_next_line(p_fd1[0], &line_fd1);
	mt_assert(strcmp(line_fd1, "111") == 0);

	get_next_line(p_fd2[0], &line_fd2);
	mt_assert(strcmp(line_fd2, "www") == 0);

	get_next_line(p_fd3[0], &line_fd3);
	mt_assert(strcmp(line_fd3, "888") == 0);

	get_next_line(p_fd0[0], &line_fd0);
	mt_assert(strcmp(line_fd0, "bbb") == 0);

	get_next_line(p_fd1[0], &line_fd1);
	mt_assert(strcmp(line_fd1, "222") == 0);

	get_next_line(p_fd2[0], &line_fd2);
	mt_assert(strcmp(line_fd2, "zzz") == 0);

	get_next_line(p_fd3[0], &line_fd3);
	mt_assert(strcmp(line_fd3, "999") == 0);
}

void test40(void)
{
	char 	*line;
	int		out;
	int		p[2];
	char 	*str;
	int		len = 50;

	str = (char *)malloc(1000 * 1000);
	*str = '\0';
	while (len--)
		strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	out = dup(1);
	pipe(p);
	dup2(p[1], 1);

	if (str)
		write(1, str, strlen(str));
	close(p[1]);
	dup2(out, 1);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, str) == 0);
}

void test41(void)
{
	clock_t start, end;

	start = clock();
	double time_spent;
	char *line;
	int fd;
	int fd2;
	int fd3
	int	diff_file_size;
    
    system("mkdir -p sandbox");
	system("openssl rand -out sandbox/large_file.txt -base64 $((50 * 1000 * 3/4)) 2> /dev/null");

	fd = open("sandbox/large_file.txt", O_RDONLY);
	fd2 = open("sandbox/large_file.txt.mine", O_CREAT | O_RDWR | O_TRUNC, 0755);

	while (get_next_line(fd, &line) == 1)
	{
	    write(fd2, line, strlen(line));
	    write(fd2, "\n", 1);
	}
	
	close(fd);
	close(fd2);

	system("diff sandbox/large_file.txt sandbox/large_file.txt.mine > sandbox/large_file.diff");
	fd3 = open("sandbox/large_file.diff", O_RDONLY);
	diff_file_size = read(fd3, NULL, 10);
	close(fd3);
	
	end = clock();
	time_spent = (end - start) / CLOCKS_PER_SEC;
	printf("%f", time_spent);

	mt_assert(diff_file_size == 0);
}

void test42(void)
{
	char *line;
	int fd;
	int fd2;
	int fd3;
	int	diff_file_size;
    
    system("mkdir -p sandbox");
	system("openssl rand -base64 $((30 * 1000 * 3/4)) | tr -d '\n' | tr -d '\r' > sandbox/one_big_fat_line.txt");
	system("echo '\n' >> sandbox/one_big_fat_line.txt");

	fd = open("sandbox/one_big_fat_line.txt", O_RDONLY);
	fd2 = open("sandbox/one_big_fat_line.txt.mine", O_CREAT | O_RDWR | O_TRUNC, 0755);

	while (get_next_line(fd, &line) == 1)
	{
	    write(fd2, line, strlen(line));
	    write(fd2, "\n", 1);
	}
	if (line)
		write(fd2, line, strlen(line));
	close(fd);
	close(fd2);

	system("diff sandbox/one_big_fat_line.txt sandbox/one_big_fat_line.txt.mine > sandbox/one_big_fat_line.diff");
	fd3 = open("sandbox/one_big_fat_line.diff", O_RDONLY);
	diff_file_size = read(fd3, NULL, 10);
	close(fd3);

	mt_assert(diff_file_size == 0);
}

int	main(void)
{
	ft_putstr("[main]");
	test01();
	get_next_line(-1, NULL);
	test02();
	get_next_line(-1, NULL);
	test03();
	get_next_line(-1, NULL);
	test04();
	get_next_line(-1, NULL);
	test05();
	get_next_line(-1, NULL);
	test06();
	get_next_line(-1, NULL);
	test07();
	get_next_line(-1, NULL);
	test08();
	get_next_line(-1, NULL);
	test09();
	get_next_line(-1, NULL);
	test10();
	get_next_line(-1, NULL);
	test11();
	get_next_line(-1, NULL);
	test12();
	get_next_line(-1, NULL);
	test13();
	get_next_line(-1, NULL);
	test14();
	get_next_line(-1, NULL);
	test15();
	get_next_line(-1, NULL);
	test16();
	get_next_line(-1, NULL);
	test17();
	get_next_line(-1, NULL);
	//test30();
	//get_next_line(-1, NULL);
	test40();
	get_next_line(-1, NULL);
	test41();
	get_next_line(-1, NULL);
	test42();
	return (0);
}
