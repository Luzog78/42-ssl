/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:36:03 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/29 00:02:02 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HEADER_H
#define __HEADER_H

#include "std.h"

#define PREFIX_SSL			"ft_ssl: "
#define PREFIX_MD5			"ft_ssl: md5: "
#define PREFIX_SHA256		"ft_ssl: sha256: "
#define PREFIX_WHIRLPOOL	"ft_ssl: whirlpool: "

#define NAME_MD5			"MD5"
#define NAME_SHA256			"SHA256"
#define NAME_WHIRLPOOL		"WHIRLPOOL"

typedef char	*(*hash_function_t)(const char *input);
typedef char	bool_t;

typedef struct ssl_s {
	char			*prefix;
	char			*hash_name;
	hash_function_t	hash_func;
	bool_t			reverse;
	bool_t			print;
	bool_t			quiet;
	char			*stdin;
	char			*string;
}	ssl_t;

char	*md5_hash(const char *message);
char	*sha256_hash(const char *message);
char	*whirlpool_hash(const char *message);

void	init_ssl(ssl_t *ssl);
int		parse_flags(ssl_t *ssl, int argc, char **argv, int i);
int		parse_stdin(ssl_t *ssl, int arg);
int		parse_files(ssl_t *ssl, int argc, char **argv, int i);
void	print_result(ssl_t *ssl, const char *input, const char *hash, int type);

#endif
