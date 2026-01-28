/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:56:27 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/28 16:57:50 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std.h"

char	*ft_read_file(const char *filename) {
	int		fd;
	char	*content;

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		errno = ENOENT;
		return NULL;
	}
	content = ft_read_content(fd);
	close(fd);
	return content;
}
