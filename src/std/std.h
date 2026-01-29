/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:50:16 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/29 01:13:32 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STD_H
#define __STD_H

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>

void	ft_err(const char *prefix, const char *message);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_put(const char *str);
char	*ft_read_content(int fd);
char	*ft_read_file(const char *filename);
size_t	ft_strlen(const char *str);

/**
 * @brief Makes the padding for the MD5 algorithm.
 *
 * @return The padded message. It must be freed by the caller.
 *
 * ---
 *
 * @note The result format is : `<message>` `0b1` `0b0 * k` `<messageBitsLength>`
 * @note
 * @note Where :
 * @note 	- `k` is the number of `0b0` bits needed to make the total bit length a multiple of 512.
 * @note 	- `messageBitsLength` is the original message length in bits represented on 64 bits.
 * @note
 * @note So `k` is calculated such as:
 * @note 	- `messageBitsLength + 1 + k ≡ 448 (mod 512)` (`+1` for the '1' bit)
 * @note 	- `k ≡ 448 - messageBitsLength - 1 (mod 512)`
 * @note 	- `K ≡ 56 - messageLength - 1 (mod 64)` (here `K = k * 8`, so the number of padding bytes)
 * @note 	- So in the code: `K = (55 - messageLength) % 64`
 * @note
 * @note Finally, the total length of the padded message is:
 * @note 	- `paddedMessageBitsLength = messageBitsLength + 1 + k + 64`
 * @note 	- `paddedMessageLength = messageLength + 1 + K + 8`
 * @note 	- So in the code: `paddedMessageLength = messageLength + pad_len + 9`
 */
uint8_t	*ft_512bit_hash_padding(const char *message, size_t *out_len, uint8_t is_little_endian);

#endif
