/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:53:06 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/28 16:55:46 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std.h"

char	*ft_read_content(int fd) {
	char	buffer[1024];
	ssize_t	bytes_read;
	size_t	total_size = 0;
	size_t	capacity = 1;

	char	*content = malloc((capacity + 1) * sizeof(char));
	if (!content) {
		errno = ENOMEM;
		return NULL;
	}

	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
		if (total_size + bytes_read >= capacity) {
			capacity += 1024;
			char *new_content = malloc((capacity + 1) * sizeof(char));
			if (!new_content) {
				free(content);
				errno = ENOMEM;
				return NULL;
			}
			for (size_t i = 0; i < total_size; i++)
				new_content[i] = content[i];
			free(content);
			content = new_content;
		}
		for (ssize_t i = 0; i < bytes_read; i++)
			content[total_size + i] = buffer[i];
		total_size += bytes_read;
	}
	if (bytes_read < 0) {
		free(content);
		errno = EIO;
		return NULL;
	}
	content[total_size] = '\0';
	return content;
}
