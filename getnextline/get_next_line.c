/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:32:55 by cbaey             #+#    #+#             */
/*   Updated: 2024/02/23 18:01:06 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	append(t_lst **list, char *buf)
{
	t_lst	*new_node;
	t_lst	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_lst));
	if (NULL == new_node)
		return ;
	if (NULL == last_node)
		*list = new_node;
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

	while (!found_newline(*list))
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
		append(list, buf);
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
	copy_str(list, next_str);
	return (next_str);
}

char	*get_next_line(int fd)
{
	static t_lst	*list = NULL;
	char			*next_line;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_lines(list);
	polish_list(&list);
	return (next_line);
}
/*
int	main(void)
{
	int	fd;  
	char	*line;
	int	lines;

	lines = 1;
	fd = open("files.txt", O_RDONLY);
	//while ((line = get_next_line(fd)
	line = get_next_line(fd);
	printf("%s", line);
	free (line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
        printf("%s", line);
        free(line);
	line = get_next_line(fd);
        printf("%s", line);
        free(line);


		
		//printf("%d->%s\n", lines++, line);
}*/
