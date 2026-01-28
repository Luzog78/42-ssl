/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:37:08 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/29 00:01:41 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MD5_H
#define __MD5_H

#include "std.h"

#define MD5_S	7, 12, 17, 22,  7, 12, 17, 22, \
				7, 12, 17, 22,  7, 12, 17, 22, \
				5,  9, 14, 20,  5,  9, 14, 20, \
				5,  9, 14, 20,  5,  9, 14, 20, \
				4, 11, 16, 23,  4, 11, 16, 23, \
				4, 11, 16, 23,  4, 11, 16, 23, \
				6, 10, 15, 21,  6, 10, 15, 21, \
				6, 10, 15, 21,  6, 10, 15, 21

#define MD5_K	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, \
				0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, \
				0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, \
				0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, \
				0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, \
				0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, \
				0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, \
				0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, \
				0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, \
				0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, \
				0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, \
				0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, \
				0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, \
				0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, \
				0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, \
				0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391

#define MD5_A0	0x67452301
#define MD5_B0	0xefcdab89
#define MD5_C0	0x98badcfe
#define MD5_D0	0x10325476

#define MD5_F(B, C, D)	((B & C) | (~B & D))
#define MD5_G(B, C, D)	((B & D) | (C & ~D))
#define MD5_H(B, C, D)	(B ^ C ^ D)
#define MD5_I(B, C, D)	(C ^ (B | ~D))
#define MD5_LROT(x, c)	((x << c) | (x >> (32 - c)))

uint8_t		*md5_pad(const char *message, size_t *out_len);
void		md5_process_chunk(const uint8_t *chunk, uint32_t *v0, const uint32_t *S, const uint32_t *K);
uint32_t	md5_M(const uint8_t *chunk, size_t g);
char		*md5_build(const uint32_t *v0);

/**
 * See https://en.wikipedia.org/wiki/MD5#Algorithm
 *
 * @return A 32-character hexadecimal string. It must be freed by the caller.
 */
char	*md5_hash(const char *message);

#endif
