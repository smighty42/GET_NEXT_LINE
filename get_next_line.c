/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:02:06 by smayti            #+#    #+#             */
/*   Updated: 2025/01/03 14:44:14 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static int	read_buffer(int fd, char **stash, char *buffer)
{
	char	*stash_temp;
	int		bytes;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0 || buffer == NULL)
	{
		free_stash(stash);
		return (-1);
	}
	if (bytes == 0)
		return (bytes);
	stash_temp = ft_strjoin(*stash, buffer);
	free(*stash);
	*stash = stash_temp;
	return (bytes);
}

static int	remove_result(char **stash)
{
	char	*sign_newline;
	char	*stash_temp;
	size_t	i;
	size_t	j;

	sign_newline = ft_strchr(*stash, '\n');
	if (!sign_newline)
	{
		free_stash(stash);
		return (1);
	}
	stash_temp = malloc((ft_strlen(sign_newline)) * sizeof(char));
	if (!stash_temp)
		return (1);
	i = 0;
	j = ft_strlen(*stash) - ft_strlen(sign_newline) + 1;
	while (j < ft_strlen(*stash))
		stash_temp[i++] = (*stash)[j++];
	stash_temp[i] = '\0';
	free(*stash);
	*stash = stash_temp;
	if (**stash == 0)
		free_stash(stash);
	return (0);
}

static int	get_result(char **stash, char **result)
{
	char	*sign_newline;
	size_t	len;
	size_t	i;

	sign_newline = ft_strchr(*stash, '\n');
	len = ft_strlen(*stash) - ft_strlen(sign_newline) + 2;
	*result = (char *)malloc(len * sizeof(char));
	if (!(*result))
		return (1);
	i = 0;
	while (i < len - 1)
	{
		(*result)[i] = (*stash)[i];
		i++;
	}
	(*result)[i] = '\0';
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*result;
	char		*buffer;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (ft_strchr(stash, '\n') == NULL && bytes > 0)
		bytes = read_buffer(fd, &stash, buffer);
	free(buffer);
	if (bytes == -1)
		return (NULL);
	if (ft_strlen(stash) == 0)
		return (NULL);
	if (get_result(&stash, &result) == 1)
		return (NULL);
	if (remove_result(&stash) == 1)
		return (NULL);
	return (result);
}
