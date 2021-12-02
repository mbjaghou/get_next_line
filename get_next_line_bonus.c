/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:49:05 by mbjaghou          #+#    #+#             */
/*   Updated: 2021/11/24 23:49:07 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_lecture(int fd, char *buffers)
{
	char	calu[BUFFER_SIZE + 1];
	int		byte;

	byte = 1;
	while (!ft_strchr(buffers, '\n') && byte)
	{
		byte = read(fd, calu, BUFFER_SIZE);
		if (byte == -1)
			return (0);
		calu[byte] = '\0';
		buffers = ft_strjoin(buffers, calu);
	}
	return (buffers);
}

char	*lire_ligne(char *buffers)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!buffers[i])
		return (0);
	while (buffers[i] != '\n' && buffers[i] != '\0')
		i++;
	if (buffers[i] == '\n')
		i++;
	tmp = (char *)malloc(sizeof (char) * i + 1);
	if (!tmp)
		return (0);
	i = 0;
	while (buffers[i] != '\n' && buffers[i] != '\0')
	{
		tmp[i] = buffers[i];
		i++;
	}
	if (buffers[i] == '\n')
		tmp[i++] = '\n';
	tmp[i] = '\0';
	return (tmp);
}

char	*chyata(char *buffers)
{
	int		i;
	char	*baki;
	int		len;
	int		j;

	i = 0;
	j = 0;
	while (buffers[i] != '\n' && buffers[i])
		i++;
	if (!buffers[i])
	{
		free (buffers);
		return (0);
	}
	len = ft_strlen(buffers) - i;
	baki = (char *)malloc(sizeof (char) * len + 1);
	if (!baki)
		return (0);
	i++;
	while (buffers[i])
		baki[j++] = buffers[i++];
	baki[j] = '\0';
	free (buffers);
	return (baki);
}

char	*get_next_line(int fd)
{
	static char	*buffers[100000];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	buffers[fd] = ft_lecture(fd, buffers[fd]);
	if (!buffers[fd])
		return (0);
	line = lire_ligne(buffers[fd]);
	buffers[fd] = chyata(buffers[fd]);
	return (line);
}
