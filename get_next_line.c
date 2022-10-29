/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 10:27:00 by cigarcia          #+#    #+#             */
/*   Updated: 2022/04/28 22:40:45 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_more(int fd, char *raw_buff)
{
	char	*buff;
	int		chars_seen;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	chars_seen = 1;
	while (!ft_strchr(raw_buff, '\n') && chars_seen != 0)
	{
		chars_seen = read(fd, buff, BUFFER_SIZE);
		if (chars_seen == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[chars_seen] = '\0';
		raw_buff = ft_strjoin(raw_buff, buff);
	}
	free(buff);
	return (raw_buff);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*raw_buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	raw_buff = read_more(fd, raw_buff);
	if (!raw_buff)
		return (NULL);
	line = get_line(raw_buff);
	raw_buff = adjust_buffer(raw_buff);
	return (line);
}
