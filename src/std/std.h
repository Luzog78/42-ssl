/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:50:16 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/28 16:58:01 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STD_H
#define STD_H

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

void	ft_err(const char *prefix, const char *message);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_put(const char *str);
char	*ft_read_content(int fd);
char	*ft_read_file(const char *filename);

#endif
