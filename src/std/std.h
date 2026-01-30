/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:50:16 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/30 13:51:54 by luzog78          ###   ########.fr       */
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
 * @brief Makes the padding for hash algorithms.
 *
 * @return The padded message. It must be freed by the caller.
 *
 * ---
 *
 * @note The result format is : `<message>` `0b1` `0b0 * k` `<messageBitsLength>`
 * @note
 * @note Where :
 * @note 	- `k` is the number of `0b0` bits needed to make the total bit length a multiple of 512.
 * @note 	- `messageBitsLength` is the original message length in bits represented on `reserved_bytes * 8` bits.
 * @note
 * @note So `k` is calculated such as:
 * @note 	- `messageBitsLength + 1 + k ≡ 512 - reserved_bytes * 8 (mod 512)` (`+1` for the '1' bit)
 * @note 	- `k ≡ 512 - reserved_bytes * 8 - messageBitsLength - 1 (mod 512)`
 * @note 	- `K ≡ 64 - reserved_bytes - messageLength - 1 (mod 64)` (here `K = k * 8`, so the number of padding bytes)
 * @note 	- So in the code: `K = (63 - reserved_bytes - messageLength) % 64`
 * @note	- And to handle negative values: `K = (((ssize_t)(...)) % 64 + 64) % 64`
 * @note
 * @note Finally, the total length of the padded message is:
 * @note 	- `paddedMessageBitsLength = messageBitsLength + 1 + k + reserved_bytes * 8`
 * @note 	- `paddedMessageLength = messageLength + 1 + K + reserved_bytes`
 * @note 	- So in the code: `paddedMessageLength = messageLength + 1 + pad_len + reserved_bytes`
 */
uint8_t	*ft_512bit_hash_padding(const char *message, size_t *out_len, size_t reserved_bytes, uint8_t is_little_endian);

#endif
