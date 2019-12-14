/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-alla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:49:13 by nel-alla          #+#    #+#             */
/*   Updated: 2019/11/09 12:19:01 by nel-alla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_clean(char **p)
{
	free(*p);
	*p = NULL;
}

char	*ft_readlines(int fd, char **rest)
{
	ssize_t		read_chars;
	char		*buffer;
	char		*temp;

	if (!*rest)
		*rest = ft_strdup("");
	if (!(buffer = malloc(BUFFER_SIZE + 1)))
		return (NULL);
	while (!ft_strchr(*rest, '\n'))
	{
		if ((read_chars = read(fd, buffer, BUFFER_SIZE)) < 0)
		{
			ft_clean(&buffer);
			return (0);
		}
		buffer[read_chars] = '\0';
		temp = *rest;
		*rest = ft_strjoin(temp, buffer);
		ft_clean(&temp);
		if (read_chars == 0 || rest[0] == '\0')
			break ;
	}
	ft_clean(&buffer);
	return (*rest);
}

int		get_next_line(int fd, char **line)
{
	static char *rest[1024];
	size_t		length;
	char		*temp;

	if (fd < 0 || !line || read(fd, *line, 0) || BUFFER_SIZE < 0)
		return (-1);
	if (!(rest[fd] = ft_readlines(fd, &rest[fd])))
		return (0);
	if (!ft_strchr(rest[fd], '\n'))
	{
		if (!(*line = ft_strdup(rest[fd])))
			return (-1);
		ft_clean(&rest[fd]);
		return (0);
	}
	length = ft_strchr(rest[fd], '\n') - rest[fd];
	temp = rest[fd];
	if (!(*line = ft_substr(rest[fd], 0, length)))
		return (-1);
	if (!(rest[fd] = ft_strdup(rest[fd] + length + 1)))
		return (-1);
	ft_clean(&temp);
	return (1);
}
