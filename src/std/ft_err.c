/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:57:27 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/28 14:59:41 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std.h"

void	ft_err(const char *prefix, const char *message) {
	size_t	len;

	if (prefix) {
		len = 0;
		while (prefix[len])
			len++;
		write(STDERR_FILENO, prefix, len);
	}
	if (message) {
		len = 0;
		while (message[len])
			len++;
		write(STDERR_FILENO, message, len);
	}
}
