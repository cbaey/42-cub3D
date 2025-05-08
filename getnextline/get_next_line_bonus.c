/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:07:14 by cbaey             #+#    #+#             */
/*   Updated: 2024/02/24 14:29:00 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

void	append(t_lst **list, int fd, char *buf)
{
	t_lst	*new_node;
	t_lst	*last_node;

	last_node = find_last_node(list[fd]);
	new_node = malloc(sizeof(t_lst));
	if (NULL == new_node)
		return ;
	if (NULL == last_node)
		list[fd] = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	polish_list(t_lst **list)
{
	t_lst	*last_node;
	t_lst	*clean_node;
	char	*buf;
	int		k;
	int		i;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_lst));
	if (NULL == buf || NULL == clean_node)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] != '\0' && last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] != '\0' && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

void	create_list(t_lst **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_newline(list[fd]))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (NULL == buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 1)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append(list, fd, buf);
	}
}

char	*get_lines(t_lst *list)
{
	int		str_len;
	char	*next_str;

	if (NULL == list)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);
	next_str[str_len] = '\0';
	copy_str(list, next_str);
	return (next_str);
}

char	*get_next_line(int fd)
{
	static t_lst	*list[1024];
	char			*next_line;

	if ((fd < 0) || (BUFFER_SIZE <= 0) || (fd > 1023))
		return (NULL);
	create_list(list, fd);
	if (list[fd] == NULL)
	{
		return (NULL);
	}
	next_line = get_lines(list[fd]);
	polish_list(&list[fd]);
	return (next_line);
}

/*
int	main()
{
	char	*str1;
//	char	*str2;
	int		fd1;
	int		fd2;

	fd1 = open("infile", O_RDWR);
	fd2 = open("infile", O_RDWR);
	while ((str1 = get_next_line(fd1)))
	{
		printf("str1 = %s\n", str1);
		free(str1);
	}
//	str2 = get_next_line(fd2);
//	printf("str1 = %s\n", str1);
//	printf("str2 = %s\n", str2);
//	str1 = get_next_line(fd1);
//	printf("str1 = %s\n", str1);
//	str1 = get_next_line(fd1);
//	printf("str1 = %s\n", str1);
//	str1 = get_next_line(fd1);
//	printf("str1 = %s\n", str1);
//	str1 = get_next_line(fd1);
//	printf("str1 = %s\n", str1);
//	str1 = get_next_line(fd1);
//	printf("str1 = %s\n", str1);
//	str1 = get_next_line(fd1);
//	printf("str1 = %s\n", str1);
//	str1 = get_next_line(fd1);
//	printf("str1 = %s\n", str1);
//	str1 = get_next_line(fd1);
//	printf("str1 = %s\n", str1);
//	str1 = get_next_line(fd1);
//	printf("str1 = %s\n", str1);
//	str2 = get_next_line(fd2);
//	printf("str2 = %s\n", str2);
//	str2 = get_next_line(fd2);
//	printf("str2 = %s\n", str2);
//	str2 = get_next_line(fd2);
//	printf("str2 = %s\n", str2);
//	str2 = get_next_line(fd2);
//	printf("str2 = %s\n", str2);
}
*/
