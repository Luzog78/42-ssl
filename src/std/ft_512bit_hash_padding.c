/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_512bit_hash_padding.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 00:49:08 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/30 13:52:17 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std.h"

#include <stdio.h>

uint8_t	*ft_512bit_hash_padding(const char *message, size_t *out_len, size_t reserved_bytes, uint8_t is_little_endian) {
	size_t	len = ft_strlen(message);
	size_t	pad_len = (((ssize_t) (63ll - reserved_bytes - len)) % 64 + 64) % 64; // See notes above

	uint8_t	*pad_msg = malloc(len + 1ull + pad_len + reserved_bytes); // See notes above
	if (!pad_msg) {
		errno = ENOMEM;
		return NULL;
	}
	*out_len = len + 1ull + pad_len + reserved_bytes;

	size_t	i;
	for (i = 0; i < len; i++)
		pad_msg[i] = (uint8_t) message[i];
	pad_msg[i++] = 0b10000000; // Append the '1' bit, then 7 '0' bits
	for (; i < len + pad_len + 1ull; i++)
		pad_msg[i] = 0b00000000; // Append 8 '0' bits

	uint64_t	bit_len = (uint64_t) len * 8ull;
	if (is_little_endian) {
		for (size_t j = 0; j < 8; j++)
			pad_msg[i + j] = (uint8_t) (bit_len >> (j * 8));
		for (size_t j = 0; j < reserved_bytes - 8; j++)
			pad_msg[i + 8 + j] = 0b00000000;
	} else {
		for (size_t j = 0; j < reserved_bytes - 8; j++)
			pad_msg[i + j] = 0b00000000;
		for (size_t j = 0; j < 8; j++)
			pad_msg[i + reserved_bytes - 8 + j] = (uint8_t) (bit_len >> (56 - j * 8));
	}
	return pad_msg;
}
