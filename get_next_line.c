/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:45:10 by ssanei            #+#    #+#             */
/*   Updated: 2024/04/29 22:04:49 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*stashed_line(char *line)
{
	char	*left_string;
	long	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	left_string = ft_substr(line, i + 1, (ft_strlen(line) - i));
	free(line);
	if (*left_string == '\0')
	{
		free(left_string);
		left_string = NULL;
	}
	return (line[i + 1] = '\0', left_string);
}

char	*read_file(int fd, char *left_string, char *buffer)
{
	long	read_bytes;
	char	*temporary;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == 0)
			break ;
		if (read_bytes < 0)
			return (free(left_string), (NULL));
		buffer[read_bytes] = '\0';
		if (!left_string)
			left_string = ft_strdup("");
		temporary = left_string;
		left_string = ft_strjoin(temporary, buffer);
		free(temporary);
		temporary = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_string);
}

char	*get_next_line(int fd)
{
	static char	*left_string;
	char		*next_line;
	char		*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd > -1 && BUFFER_SIZE > 0 && read(fd, 0, 0) > -1)
	{
		if (!buffer)
			return (NULL);
		next_line = read_file(fd, left_string, buffer);
		free(buffer);
		buffer = NULL;
		if (!next_line)
			return (NULL);
		return (left_string = stashed_line(next_line), (next_line));
	}
	else
		return (free(left_string), free(buffer), (NULL));
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("get_next_line.c", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("line: %s", line);
	}
	close(fd);
	return (0);
}
