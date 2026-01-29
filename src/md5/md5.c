/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:39:40 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/29 01:13:58 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

/**
 * @brief Extracts the g-th 32-bit word from the given 512-bit chunk.
 *
 * @param chunk The 512-bit (64 bytes) chunk.
 * @param g The index of the 32-bit (4 bytes) word to extract (0 to 15).
 *
 * @return The extracted 32-bit word in little-endian format. (Very important!)
 */
uint32_t	md5_M(const uint8_t *chunk, size_t g) {
	return (((uint32_t) chunk[g * 4]))					// Least significant byte
			| (((uint32_t) chunk[g * 4 + 1]) << 8)
			| (((uint32_t) chunk[g * 4 + 2]) << 16)
			| (((uint32_t) chunk[g * 4 + 3]) << 24);	// Most significant byte
}

void	md5_process_chunk(const uint8_t *chunk, uint32_t *v0, const uint32_t *S, const uint32_t *K) {
	uint32_t	A = v0[0];
	uint32_t	B = v0[1];
	uint32_t	C = v0[2];
	uint32_t	D = v0[3];

	for (size_t i = 0; i < 64; i++) {
		uint32_t	F;
		size_t		g;

		if (i < 16) {
			F = MD5_F(B, C, D);
			g = i;
		} else if (i < 32) {
			F = MD5_G(B, C, D);
			g = (5 * i + 1) % 16;
		} else if (i < 48) {
			F = MD5_H(B, C, D);
			g = (3 * i + 5) % 16;
		} else {
			F = MD5_I(B, C, D);
			g = (7 * i) % 16;
		}

		F = F + A + K[i] + md5_M(chunk, g);
		A = D;
		D = C;
		C = B;
		B = B + MD5_LROT(F, S[i]);
	}

	v0[0] += A;
	v0[1] += B;
	v0[2] += C;
	v0[3] += D;
}

/**
 * @brief Builds the final MD5 hash string from the state variables.
 *
 * @return A 32-character hexadecimal string. It must be freed by the caller.
 *
 * @note The state variables are in little-endian format.
 */
char	*md5_build(const uint32_t *v0) {
	char	*hash = malloc(33); // 32 chars + null terminator
	if (!hash) {
		errno = ENOMEM;
		return NULL;
	}

	const char	*hex_chars = "0123456789abcdef";
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++) {
			hash[i * 8 + j * 2] = hex_chars[(v0[i] >> (j * 8 + 4)) & 0xF];
			hash[i * 8 + j * 2 + 1] = hex_chars[(v0[i] >> (j * 8)) & 0xF];
		}
	hash[32] = '\0';
	return hash;
}

char	*md5_hash(const char *message) {
	const uint32_t	S[] = { MD5_S };
	const uint32_t	K[] = { MD5_K };

	size_t			len;
	uint8_t			*padded = ft_512bit_hash_padding(message, &len, 1); // little-endian
	uint32_t		v0[] = { MD5_A0, MD5_B0, MD5_C0, MD5_D0 };

	if (!padded)
		return NULL;
	for (size_t chunk = 0; chunk < len; chunk += 64)
		md5_process_chunk(&padded[chunk], v0, S, K);
	free(padded);
	return md5_build(v0);
}
