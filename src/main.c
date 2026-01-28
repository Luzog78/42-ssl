/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:39:40 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/28 16:45:57 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_help() {
	ft_put("Usage: ft_ssl <hash_function> [options] [--] [files...]\n");
	ft_put("\n");
	ft_put("Hash functions:\n");
	ft_put("  md5         Compute MD5 hash\n");
	ft_put("  sha256      Compute SHA-256 hash\n");
	ft_put("  whirlpool   Compute Whirlpool hash\n");
	ft_put("\n");
	ft_put("Options:\n");
	ft_put("  -h, --help             Display this help message\n");
	ft_put("  -r, --reverse          Display the hash in reverse order\n");
	ft_put("  -p, --print            Print the input string\n");
	ft_put("  -s, --string <string>  Hash the given string\n");
	ft_put("  -q, --quiet            Suppress non-hash output\n");
	ft_put("\n");
}

int	main(int argc, char **argv) {
	ssl_t	ssl;

	if (argc < 2)
		return ft_err(PREFIX_SSL, "Error: No hash function specified.\n"), -1;

	init_ssl(&ssl);
	if (argc < 3 || ft_strcmp(argv[1], "-h") == 0 || ft_strcmp(argv[1], "--help") == 0)
		return print_help(), 0;
	else if (ft_strcmp(argv[1], "md5") == 0) {
		ssl.prefix = PREFIX_MD5;
		ssl.hash_name = NAME_MD5;
		ssl.hash_func = md5_hash;
	} else if (ft_strcmp(argv[1], "sha256") == 0) {
		ssl.prefix = PREFIX_SHA256;
		ssl.hash_name = NAME_SHA256;
		ssl.hash_func = sha256_hash;
	} else if (ft_strcmp(argv[1], "whirlpool") == 0) {
		ssl.prefix = PREFIX_WHIRLPOOL;
		ssl.hash_name = NAME_WHIRLPOOL;
		ssl.hash_func = whirlpool_hash;
	} else
		return ft_err(PREFIX_SSL, "Error: Invalid hash function specified.\n"), -1;

	int	arg = parse_flags(&ssl, argc, argv, 2);
	if (arg > 0 && (ssl.print || (!ssl.string && arg >= argc)))
		arg = parse_stdin(&ssl, arg);
	if (arg <= 0)
		return arg;
	return parse_files(&ssl, argc, argv, arg);
}
