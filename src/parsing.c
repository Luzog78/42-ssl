/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:45:21 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/28 17:07:27 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_ssl(ssl_t *ssl) {
	ssl->prefix = NULL;
	ssl->hash_name = NULL;
	ssl->hash_func = NULL;
	ssl->reverse = 0;
	ssl->print = 0;
	ssl->quiet = 0;
	ssl->string = NULL;
	ssl->stdin = NULL;
}

int	parse_stdin(ssl_t *ssl, int arg) {
	ssl->stdin = ft_read_content(STDIN_FILENO);
	if (!ssl->stdin) {
		if (errno == ENOMEM)
			return ft_err(PREFIX_SSL, "Error: Memory allocation failed for stdin input.\n"), -1;
		if (errno == EIO)
			return ft_err(PREFIX_SSL, "Error: Failed to read from stdin.\n"), -1;
		return ft_err(PREFIX_SSL, "Error: Unknown error occurred while reading from stdin.\n"), -1;
	}
	return arg;
}

int	parse_flags(ssl_t *ssl, int argc, char **argv, int i) {
	for (; i < argc; i++)
		if (ft_strcmp(argv[i], "-r") == 0 || ft_strcmp(argv[i], "--reverse") == 0)
			ssl->reverse = 1;
		else if (ft_strcmp(argv[i], "-p") == 0 || ft_strcmp(argv[i], "--print") == 0)
			ssl->print = 1;
		else if (ft_strcmp(argv[i], "-s") == 0 || ft_strcmp(argv[i], "--string") == 0) {
			if (i + 1 < argc)
				ssl->string = argv[++i];
			else
				return ft_err(PREFIX_SSL, "Error: No string provided for -s/--string option.\n"), -1;
		} else if (ft_strcmp(argv[i], "-q") == 0 || ft_strcmp(argv[i], "--quiet") == 0)
			ssl->quiet = 1;
		else if (ft_strcmp(argv[i], "--") == 0) {
			i++;
			break;
		} else
			break;
	return i;
}

int	parse_files(ssl_t *ssl, int argc, char **argv, int i) {
	int		err_count = 0;
	char	*content;
	char	*hash;

	if (ssl->stdin) {
		hash = ssl->hash_func(ssl->stdin);
		if (!hash) {
			ft_err(ssl->prefix, "Error: Failed to compute hash for stdin input.\n");
			err_count++;
		} else
			print_result(ssl, ssl->stdin, hash, 0);
	}
	if (ssl->string) {
		hash = ssl->hash_func(ssl->string);
		if (!hash) {
			ft_err(ssl->prefix, "Error: Failed to compute hash for string input.\n");
			err_count++;
		} else
			print_result(ssl, ssl->string, hash, 1);
	}
	for (; i < argc; i++) {
		content = ft_read_file(argv[i]);
		if (!content) {
			ft_err(PREFIX_SSL, "Error: Failed to read file '");
			if (errno == ENOMEM)
				ft_err(argv[i], "' (Memory allocation failed).\n");
			else if (errno == EIO)
				ft_err(argv[i], "' (Failed to read).\n");
			else if (errno == ENOENT)
				ft_err(argv[i], "' (Cannot open file).\n");
			else
				ft_err(argv[i], "' (Unknown error occurred).\n");
			err_count++;
			continue;
		}
		hash = ssl->hash_func(content);
		free(content);
		if (!hash) {
			ft_err(ssl->prefix, "Error: Failed to compute hash for file '");
			ft_err(argv[i], "'.\n");
			err_count++;
			continue;
		}
		print_result(ssl, argv[i], hash, 2);
	}
	return err_count;
}

/**
 * @param ssl The SSL context containing options and hash function.
 * @param input The input string or file name.
 * @param hash The computed hash value.
 * @param type The type of input: `0` -> stdin, `1` -> string, `2` -> file.
 */
void	print_result(ssl_t *ssl, const char *input, const char *hash, int type) {
	if (ssl->quiet) {
		if (type == 0 && ssl->print) {
			ft_put(input);
			ft_put("\n");
		}
		ft_put(hash);
		ft_put("\n");
		return;
	}
	if (type != 0 && ssl->reverse) {
		ft_put(hash);
		ft_put(" ");
		if (type == 1)
			ft_put("\"");
		ft_put(input);
		if (type == 1)
			ft_put("\"");
	} else {
		if (type == 0) {
			if (ssl->print) {
				ft_put("(\"");
				ft_put(input);
				ft_put("\")= ");
			} else
				ft_put("(stdin)= ");
		} else {
			ft_put(ssl->hash_name);
			ft_put(" (");
			if (type == 1)
				ft_put("\"");
			ft_put(input);
			if (type == 1)
				ft_put("\"");
			ft_put(") = ");
		}
		ft_put(hash);
	}
	ft_put("\n");
}
