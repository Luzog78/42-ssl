/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:36:03 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/28 14:38:21 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

char	*md5_hash(const char *input);
char	*sha256_hash(const char *input);
char	*whirlpool_hash(const char *input);

#endif
