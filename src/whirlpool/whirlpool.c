/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whirlpool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:39:40 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/30 13:20:20 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whirlpool.h"

void	m8x8_copy(m8x8_uint8_t out, const m8x8_uint8_t a) {
	for (size_t i = 0; i < 64; i++)
		out[i] = a[i];
}

void	m8x8_xor(m8x8_uint8_t out_a, const m8x8_uint8_t b) {
	for (size_t i = 0; i < 64; i++)
		out_a[i] ^= b[i];
}

void	m8x8_init(m8x8_uint8_t out, const uint8_t chunk[64]) {
	for (size_t i = 0; i < 64; i++)
		out[i] = chunk[i];
}

void	whirlpool_round_constants(m8x8_uint8_t out_cr, const uint32_t r,
			const m16x16_uint8_t S) {
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 8; j++)
			out_cr[i * 8 + j] = i == 0 ? S[8 * (r - 1) + j] : 0;
}

void	whirlpool_substitution(m8x8_uint8_t out, const m16x16_uint8_t S) {
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 8; j++)
			out[i * 8 + j] = S[out[i * 8 + j]];
}

void	whirlpool_cyclical_permutation(m8x8_uint8_t out) {
	m8x8_uint8_t	tmp;

	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 8; j++)
			tmp[i * 8 + j] = out[((i - j + 8) % 8) * 8 + j];

	m8x8_copy(out, tmp);
}

void	whirlpool_linear_diffusion(m8x8_uint8_t out, const m8x8_uint8_t C) {
	m8x8_uint8_t tmp;

	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 8; j++) {
			tmp[i * 8 + j] = 0;
			for (size_t k = 0; k < 8; k++) {
				// Galois Field (2^8) multiplication
				uint32_t	a = out[i * 8 + k];
				uint32_t	b = C[k * 8 + j];
				uint32_t	product = 0;

				while (b) {
					if (b & 1)
						product ^= a;
					uint32_t	hi_bit_set = a & 0x80;
					a <<= 1;
					if (hi_bit_set)
						a ^= 0x11D; // x^8 + x^4 + x^3 + x^2 + 1
					b >>= 1;
				}
				tmp[i * 8 + j] ^= product;
			}
		}
	}

	m8x8_copy(out, tmp);
}

void	whirlpool_round(m8x8_uint8_t out, m8x8_uint8_t key,
			const m16x16_uint8_t S, const m8x8_uint8_t C) {
	whirlpool_substitution(out, S); // [3.7] `out = γ(out)`
	whirlpool_cyclical_permutation(out); // [3.7] `out = π(out)`
	whirlpool_linear_diffusion(out, C); // [3.7] `out = θ(out)`
	m8x8_xor(out, key); // [3.7] `out = σ[k](out)`
}

void	whirlpool_process_chunk(const m8x8_uint8_t chunk, m8x8_uint8_t out_key,
			const m16x16_uint8_t S, const m8x8_uint8_t C) {
	// Cipher W
	m8x8_uint8_t	W;
	m8x8_uint8_t	Kr;
	m8x8_uint8_t	cr;

	m8x8_copy(W, chunk); // [3.9] `W[k](chunk)`
	m8x8_copy(Kr, out_key); // [3.8] `K^0 = K`

	m8x8_xor(W, out_key); // [3.9] `◦ σ[K^0]`
	for (size_t r = 1; r <= WHIRLPOOL_R; r++) {
		whirlpool_round_constants(cr, r, S); // Calc `c^r`
		whirlpool_round(Kr, cr, S, C); // [3.8] `K^r = ρ[c^r](K^{r−1})`, `r > 0`
		whirlpool_round(W, Kr, S, C); // [3.9] `◦_{1}^{r=R} ρ[K^r]`
	}

	// Compression
	m8x8_xor(out_key, W); // [3.11] `W[H_{i−1}](η_i) ⊕ H_{i−1}`
	m8x8_xor(out_key, chunk); // [3.11] `⊕ η`
}

char	*whirlpool_build(const m8x8_uint8_t matrix) {
	char	*hash = malloc(129); // 128 chars + null terminator
	if (!hash) {
		errno = ENOMEM;
		return NULL;
	}

	const char *hex_chars = "0123456789ABCDEF";
	for (size_t i = 0; i < 64; i++) {
		uint8_t byte = matrix[i];
		hash[i * 2] = hex_chars[byte >> 4];
		hash[i * 2 + 1] = hex_chars[byte & 0xF];
	}
	hash[128] = '\0';
	return hash;
}

char	*whirlpool_hash(const char *message) {
	const m16x16_uint8_t	S = { WHIRLPOOL_S };
	const m8x8_uint8_t		C = { WHIRLPOOL_C };

	size_t			len;
	uint8_t			*padded = ft_512bit_hash_padding(message, &len, 32, 0); // 256-bit length, big-endian
	m8x8_uint8_t	H = { WHIRLPOOL_IV }; // [3.11] `H_0 = μ(IV)`
	m8x8_uint8_t	chunk;

	if (!padded)
		return NULL;
	for (size_t chunk_idx = 0; chunk_idx < len; chunk_idx += 64) {
		m8x8_init(chunk, &padded[chunk_idx]); // [3.11] `η_i = μ(m_i)`
		whirlpool_process_chunk(chunk, H, S, C); // [3.11] `H_i = W[H_{i−1}](η_i) ⊕ H_{i−1} ⊕ η_i`, `1 <= i <= t`
	}
	free(padded);
	return whirlpool_build(H); // [3.12] `Whirlpool(M) ≡ μ^{−1}(H_t)`
}
