/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:01:45 by akanbari          #+#    #+#             */
/*   Updated: 2024/01/31 22:53:23 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	check_new_line(char *buf)
{
	int	i;

	if (!buf)
		return (0);
	i = -1;
	while (buf[++i])
		if (buf[i] == '\n')
			return (i + 1);
	return (0);
}

int	read_buf(char **buf, char **static_array, int fd)
{
	int	char_read;

	*buf = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof (char));
	if (!(*buf))
		return (0);
	char_read = read(fd, *buf, BUFFER_SIZE);
	if (char_read == -1)
	{
		free(*buf);
		*buf = 0;
		free(*static_array);
		*static_array = 0;
		return (-1);
	}
	else if (char_read == 0)
	{
		free(*buf);
		*buf = 0;
	}
	else
		(*buf)[char_read] = 0;
	return (char_read);
}

char	*get_the_line(char **array, int char_read, int line_to_newline)
{
	char	*next_line;
	char	*buffer;
	int		buffer_len;
	int		final_len;

	buffer_len = ft_gstrlen(*array);
	final_len = buffer_len - char_read + line_to_newline;
	next_line = ft_strndup(*array, final_len);
	buffer = ft_strndup(*array + final_len, char_read - line_to_newline);
	free(*array);
	*array = buffer;
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char		*array[1024];
	char			*str;
	int				char_read;
	int				lento_newline;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	if (!array[fd] || !array[fd][0])
		char_read = read_buf(&array[fd], &array[fd], fd);
	else
		char_read = ft_gstrlen(array[fd]);
	lento_newline = check_new_line(array[fd]);
	while (lento_newline == 0 && char_read > 0)
	{
		char_read = read_buf(&str, &array[fd], fd);
		if (char_read == -1)
			break ;
		lento_newline = check_new_line(str);
		array[fd] = strnjoin(&array[fd], &str);
	}
	if (char_read <= 0 && !array[fd])
		return (0);
	return (get_the_line(&array[fd], char_read, lento_newline));
}
