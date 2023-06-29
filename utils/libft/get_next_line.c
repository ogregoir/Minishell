/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:07:09 by ogregoir          #+#    #+#             */
/*   Updated: 2023/04/07 13:59:23 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_buf(int fd, char *buf)
{
	int			ret;
	char		*temp;

	ret = 1;
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		buf = ft_calloc(1, 1);
	while (ret > 0)
	{
		ret = read(fd, temp, BUFFER_SIZE);
		if (ret < 0)
		{
			free(temp);
			free(buf);
			return (NULL);
		}
		temp[ret] = '\0';
		buf = ft_strjoin_free(buf, temp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(temp);
	return (buf);
}

char	*ft_get_line(char *buf)
{
	int		i;
	char	*line;

	i = 0;
	if (!buf[i])
		return (0);
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	}
	else
		line[i] = '\0';
	return (line);
}

char	*nextbuf(char *buf)
{
	char	*newbuf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	if (!buf[i])
	{
		free(buf);
		return (0);
	}
	newbuf = malloc(sizeof(char) * (ft_strlen(buf) - (i)));
	i++;
	while (buf[i] != '\0')
	{
		newbuf[j] = buf[i];
		i++;
		j++;
	}
	newbuf[j] = '\0';
	free(buf);
	return (newbuf);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0)
	{
		if (buf)
		{
			free(buf);
			buf = 0;
		}
		return (NULL);
	}
	buf = get_buf(fd, buf);
	if (!buf)
	{
		free(buf);
		return (NULL);
	}
	line = ft_get_line(buf);
	buf = nextbuf(buf);
	return (line);
}
