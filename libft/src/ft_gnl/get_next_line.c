/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:35:46 by gdumas            #+#    #+#             */
/*   Updated: 2024/01/31 13:27:40 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_endline(char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (0);
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] == '\n')
		return (i + 1);
	return (0);
}

char	*extract_buffer_in_line(char *buffer, char *line)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (!buffer[0])
		return (line);
	while (line[i])
		i++;
	while (buffer[j] && buffer[j - 1] != '\n')
		j++;
	new_line = (char *) malloc ((i + j + 1) * sizeof(char));
	if (!new_line)
		return (free(line), NULL);
	new_line[0] = '\0';
	ft_strlcat(new_line, line, i + 1);
	ft_strlcat(new_line, buffer, i + j + 1);
	return (free(line), new_line);
}

int	erase_printed_buff(char *buffer_dest, char *buffer_src, char **line)
{
	int	i;

	i = 0;
	if (!buffer_dest[0] || buffer_src == buffer_dest)
		return (1);
	while (buffer_src[i])
	{
		buffer_dest[i] = buffer_src[i];
		i++;
	}
	buffer_dest[i] = '\0';
	(*line) = extract_buffer_in_line(buffer_dest, (*line));
	if (!(*line))
		return (0);
	return (1);
}

char	*read_and_extract(int fd, char *buffer, char *line)
{
	ssize_t	bytesread;

	bytesread = 1;
	while (bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
		{
			buffer[0] = '\0';
			break ;
		}
		buffer[bytesread] = '\0';
		line = extract_buffer_in_line(buffer, line);
		if (!line)
			return (NULL);
		if ((check_endline(line) || bytesread == 0) && line[0])
			return (line);
	}
	return (free(line), NULL);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = "";
	char		*line;

	line = ft_strdup("");
	if (fd < 0 || !line || BUFFER_SIZE < 1
		|| !erase_printed_buff(buffer, &buffer[check_endline(buffer)], &line))
		return (free(line), NULL);
	if (check_endline(line))
		return (line);
	line = read_and_extract(fd, buffer, line);
	if (line == NULL)
		return (NULL);
	return (line);
}
