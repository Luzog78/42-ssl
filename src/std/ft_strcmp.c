/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:02:25 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/28 15:14:45 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std.h"

int	ft_strcmp(const char *s1, const char *s2) {
	size_t	i;

	if (!s1 && !s2)
		return 0;

	if (!s1)
		return -(unsigned char) s2[0];

	if (!s2)
		return (unsigned char) s1[0];

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
