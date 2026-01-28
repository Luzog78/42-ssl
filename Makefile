# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/19 13:16:00 by ysabik            #+#    #+#              #
#    Updated: 2026/01/28 14:34:54 by luzog78          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ssl

SRCS		= src/main.c \
				src/md5/md5.c \
				src/sha256/sha256.c \
				src/whirlpool/whirlpool.c
BUILD_DIR	= build
OBJS		= $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))
INCLUDES	= src src/md5 src/sha256 src/whirlpool

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g $(addprefix -I, $(INCLUDES))


all: $(NAME)


help:
	@echo "Available targets:"
	@echo "  all       - Build all components"
	@echo "  $(NAME)    - Build all components"
	@echo
	@echo "  clean     - Remove object files"
	@echo "  fclean    - Remove all artifacts"
	@echo "  re        - Rebuild all components"
	@echo
	@echo "  help      - Show this help message"


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJS) $(BUILD_DIR)


fclean: clean
	rm -f $(NAME)


re: fclean all


.PHONY: all help clean fclean re
