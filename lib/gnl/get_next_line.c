/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:08:21 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/03 23:55:08 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lib_42.h"

static char	*gnl_join(char *s1, char *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = -1;
	j = -1;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free (s1);
	return (str);
}

static char	*ft_restbuffer(char *buffer)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free (buffer);
		return (NULL);
	}
	rest = (char *) malloc ((ft_strlen(buffer)) - i + 1 * sizeof(char));
	if (!rest)
		return (NULL);
	if (buffer[i] && buffer[i] == '\n')
	{
		i++;
		while (buffer[i])
			rest[j++] = buffer[i++];
		rest[j] = '\0';
	}
	free (buffer);
	return (rest);
}

static char	*ft_getrow(char *buffer)
{
	char	*row;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		row = (char *) malloc (i + 2 * sizeof(char));
	else
		row = (char *) malloc (i + 1 * sizeof(char));
	if (!row)
		return (NULL);
	i = -1;
	while (buffer[++i] && buffer[i] != '\n')
		row[i] = buffer[i];
	if (buffer[i] == '\n')
	{
		row[i] = buffer[i];
		i++;
	}
	row[i] = '\0';
	return (row);
}

static char	*ft_readit(int fd, char *buffer)
{
	char	*row;
	int		i;

	row = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!row)
		return (NULL);
	i = 1;
	while (!ft_strchr(buffer, '\n') && i > 0)
	{
		i = read(fd, row, BUFFER_SIZE);
		if (i == -1)
		{
			free (row);
			if (buffer)
				free (buffer);
			return (NULL);
		}
		row[i] = '\0';
		buffer = gnl_join(buffer, row);
	}
	free (row);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FOPEN_MAX];
	char		*row;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_readit(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	row = ft_getrow(buffer[fd]);
	buffer[fd] = ft_restbuffer(buffer[fd]);
	return (row);
}
