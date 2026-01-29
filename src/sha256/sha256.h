/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:37:08 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/29 01:05:08 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SHA256_H
#define __SHA256_H

#include "std.h"

#define SHA256_K	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, \
					0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, \
					0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, \
					0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, \
					0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, \
					0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, \
					0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, \
					0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, \
					0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, \
					0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, \
					0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, \
					0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, \
					0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, \
					0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, \
					0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, \
					0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2

#define SHA256_H0	0x6a09e667
#define SHA256_H1	0xbb67ae85
#define SHA256_H2	0x3c6ef372
#define SHA256_H3	0xa54ff53a
#define SHA256_H4	0x510e527f
#define SHA256_H5	0x9b05688c
#define SHA256_H6	0x1f83d9ab
#define SHA256_H7	0x5be0cd19

#define SHA256_Ch(E, F, G)	((E & F) ^ (~E & G))
#define SHA256_Maj(A, B, C)	((A & B) ^ (A & C) ^ (B & C))
#define SHA256_RROT(x, c)	((x >> c) | (x << (32 - c)))


void	sha256_fill_w(const uint8_t *padded, uint32_t w[64]);
void	sha256_process_chunk(const uint8_t *chunk, uint32_t *h, const uint32_t *K);
char	*sha256_build(const uint32_t *v0);

/**
 * See https://en.wikipedia.org/wiki/SHA-2#Pseudocode
 *
 * @return A 64-character hexadecimal string. It must be freed by the caller.
 */
char	*sha256_hash(const char *message);

#endif
