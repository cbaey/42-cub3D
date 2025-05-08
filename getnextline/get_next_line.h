/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:34:25 by cbaey             #+#    #+#             */
/*   Updated: 2024/01/10 18:41:03 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct t_linklst
{
	char				*str_buf;
	struct t_linklst	*next;
}	t_lst;

void	append(t_lst **list, char *buf);
void	create_list(t_lst **list, int fd);
char	*get_lines(t_lst *list);
int		len_to_newline(t_lst *list);
void	copy_str(t_lst *list, char *str);
void	polish_list(t_lst **list);
t_lst	*find_last_node(t_lst *list);
int		found_newline(t_lst *list);
void	dealloc(t_lst **list, t_lst *clean_node, char *buf);
char	*get_next_line(int fd);

#endif
