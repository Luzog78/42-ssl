/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:07:46 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/28 15:14:04 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std.h"

ssize_t	ft_put(const char *str) {
	size_t	len;

	if (!str)
		return -1;

	len = 0;
	while (str[len])
		len++;
	return write(STDOUT_FILENO, str, len);
}
