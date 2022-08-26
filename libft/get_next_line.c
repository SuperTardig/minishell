/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:40:41 by fleduc            #+#    #+#             */
/*   Updated: 2022/06/07 15:58:33 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_sl(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == '\n')
			return (i + 1);
	return (i);
}

int	ft_check_eof(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		++i;
	return (buffer[i] != '\n');
}

void	ft_clean_buffer(char *buffer)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (buffer[++i])
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			break ;
		}
		buffer[i] = '\0';
	}
	while (buffer[++i])
	{
		buffer[++j] = buffer[i];
		buffer[i] = '\0';
	}
}

char	*ft_get_the_line(char *line, char *buffer)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = -1;
	tmp = line;
	line = ft_calloc((ft_sl(line) + ft_sl(buffer) + 1), sizeof(char));
	if (!line)
		return (NULL);
	while (tmp && tmp[i])
	{
		line[i] = tmp[i];
		++i;
	}
	while (buffer[++j])
	{
		line[i + j] = buffer[j];
		if (buffer[j] == '\n')
			break ;
	}
	if (tmp)
		free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*line;
	int			eof;
	int			read_chars;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	eof = 1;
	read_chars = 1;
	line = NULL;
	while (eof)
	{
		if (!buffer[0])
			read_chars = read(fd, buffer, BUFFER_SIZE);
		if (ft_check_eof(buffer) && read_chars >= 1)
			eof = 1;
		else
			eof = 0;
		if (read_chars >= 1)
			line = ft_get_the_line(line, buffer);
		ft_clean_buffer(buffer);
	}
	return (line);
}
