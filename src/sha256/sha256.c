/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:39:40 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/30 12:56:15 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

void	sha256_fill_w(const uint8_t *padded, uint32_t w[64]) {
	size_t	t;
	for (t = 0; t < 16; t++) {
		w[t] = (((uint32_t) padded[t * 4]) << 24)
				| (((uint32_t) padded[t * 4 + 1]) << 16)
				| (((uint32_t) padded[t * 4 + 2]) << 8)
				| (((uint32_t) padded[t * 4 + 3]));
	}
	for (; t < 64; t++) {
		uint32_t	s0 = SHA256_RROT(w[t - 15], 7) ^ SHA256_RROT(w[t - 15], 18) ^ (w[t - 15] >> 3);
		uint32_t	s1 = SHA256_RROT(w[t - 2], 17) ^ SHA256_RROT(w[t - 2], 19) ^ (w[t - 2] >> 10);
		w[t] = w[t - 16] + s0 + w[t - 7] + s1;
	}
}

void	sha256_process_chunk(const uint8_t *chunk, uint32_t *h, const uint32_t *K) {
	uint32_t	A = h[0];
	uint32_t	B = h[1];
	uint32_t	C = h[2];
	uint32_t	D = h[3];
	uint32_t	E = h[4];
	uint32_t	F = h[5];
	uint32_t	G = h[6];
	uint32_t	H = h[7];

	uint32_t	w[64];
	sha256_fill_w(chunk, w);

	for (size_t t = 0; t < 64; t++) {
		uint32_t	S1 = SHA256_RROT(E, 6) ^ SHA256_RROT(E, 11) ^ SHA256_RROT(E, 25);
		uint32_t	ch = SHA256_Ch(E, F, G);
		uint32_t	temp1 = H + S1 + ch + K[t] + w[t];
		uint32_t	S0 = SHA256_RROT(A, 2) ^ SHA256_RROT(A, 13) ^ SHA256_RROT(A, 22);
		uint32_t	maj = SHA256_Maj(A, B, C);
		uint32_t	temp2 = S0 + maj;

		H = G;
		G = F;
		F = E;
		E = D + temp1;
		D = C;
		C = B;
		B = A;
		A = temp1 + temp2;
	}
	h[0] += A;
	h[1] += B;
	h[2] += C;
	h[3] += D;
	h[4] += E;
	h[5] += F;
	h[6] += G;
	h[7] += H;
}

char	*sha256_build(const uint32_t *h) {
	char	*hash_str = malloc(65); // 64 chars + null terminator
	if (!hash_str) {
		errno = ENOMEM;
		return NULL;
	}

	const char	*hex_chars = "0123456789abcdef";
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 4; j++) {
			uint8_t byte = (h[i] >> (24 - j * 8)) & 0xFF;
			hash_str[i * 8 + j * 2] = hex_chars[byte >> 4];
			hash_str[i * 8 + j * 2 + 1] = hex_chars[byte & 0xF];
		}
	hash_str[64] = '\0';
	return hash_str;
}

char	*sha256_hash(const char *message) {
	const uint32_t	K[] = { SHA256_K };

	size_t			len;
	uint8_t			*padded = ft_512bit_hash_padding(message, &len, 8, 0); // 64-bit length, big-endian
	uint32_t		h[] = {	SHA256_H0, SHA256_H1, SHA256_H2, SHA256_H3,
							SHA256_H4, SHA256_H5, SHA256_H6, SHA256_H7 };

	if (!padded)
		return NULL;
	for (size_t chunk = 0; chunk < len; chunk += 64)
		sha256_process_chunk(&padded[chunk], h, K);
	free(padded);
	return sha256_build(h);
}
