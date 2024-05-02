/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:35:46 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:58:38 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if there is an endline character in the source string.
 * 
 * @param src The source string to check.
 * @return {int} Returns the index of the endline character
 * plus one if it exists, otherwise returns FALSE.
 */
static int	check_endline(char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (FALSE);
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] == '\n')
		return (i + 1);
	return (FALSE);
}

/**
 * @brief Extracts a line from the buffer and appends it to the existing line.
 * 
 * @param buffer The buffer containing the data to extract.
 * @param line The existing line to append to.
 * @return {char*} Returns a pointer to the new line,
 * or NULL if an error occurred.
 */
static char	*extract_buffer_in_line(char *buffer, char *line)
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

/**
 * @brief Erases the printed buffer and extracts a line from the source buffer.
 * 
 * @param buffer_dest The destination buffer to erase.
 * @param buffer_src The source buffer to extract from.
 * @param line A pointer to the line to extract to.
 * @return {int} Returns TRUE if successful, otherwise returns FALSE.
 */
static int	erase_printed_buff(char *buffer_dest, char *buffer_src, char **line)
{
	int	i;

	i = 0;
	if (!buffer_dest[0] || buffer_src == buffer_dest)
		return (TRUE);
	while (buffer_src[i])
	{
		buffer_dest[i] = buffer_src[i];
		i++;
	}
	buffer_dest[i] = '\0';
	(*line) = extract_buffer_in_line(buffer_dest, (*line));
	if (!(*line))
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Reads data from a file descriptor and extracts a line from the buffer.
 * 
 * @param fd The file descriptor to read from.
 * @param buffer The buffer to extract a line from.
 * @param line The existing line to append to.
 * @return {char*} Returns a pointer to the new line,
 * or NULL if an error occurred.
 */
static char	*read_and_extract(int fd, char *buffer, char *line)
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

/**
 * @brief Gets the next line from a file descriptor.
 * 
 * @param fd The file descriptor to get the next line from.
 * @return {char*} Returns a pointer to the next line,
 * or NULL if an error occurred.
 */
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
