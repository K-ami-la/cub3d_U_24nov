# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaizatov <kaizatov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 22:22:35 by ulmagner          #+#    #+#              #
#    Updated: 2025/11/25 17:25:10 by kaizatov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
	
LFT_NAME	= libft.a

MLX_NAME	= libmlx.a

SRCS		= main.c clear.c init_map.c init_map_bis.c free.c floodfill.c \
get_info.c error_handling.c launcher.c pixel_put.c movement.c tileset.c \
display_map.c dda.c floor_ceiling.c \
hooks.c minimap.c mouse.c init.c sprites.c dda_utils.c movement_utils.c \
get_info_utils.c \

INCS		= cub3d.h
INCS_B		= allb.h
INCS_LFT	= libft.h
INCS_MLX	= mlx.h
SDIRS		= srcs
SDIRS_B		= srcsb
IDIRS		= includes
IDIRS_B		= includesb
IDIRS_LFT	= includes/libfts/includes
IDIRS_MLX	= includes/minilibx-linux
ODIRS		= objs
ODIRS_B		= objs_b
DIRS_LFT	= includes/libfts
DIRS_MLX	= includes/minilibx-linux

IFILES		= $(addprefix $(IDIRS)/,$(INCS))
IFILES_B	= $(addprefix $(IDIRS)/,$(INCS))
IFILES_LFT	= $(addprefix $(IDIRS_LFT)/,$(INCS_LFT))
IFILES_MLX	= $(addprefix $(IDIRS_MLX)/,$(INCS_MLX))
SFILES		= $(addprefix $(SDIRS)/,$(SRCS))
SFILES_B	= $(addprefix $(SDIRS_B)/,$(SRCS_B))
OFILES		= $(addprefix $(ODIRS)/,$(patsubst %.c,%.o,$(SRCS)))
OFILES_B	= $(addprefix $(ODIRS_B)/,$(patsubst %.c,%.o,$(SRCS_B)))
A_LFT		= $(addprefix $(DIRS_LFT)/,$(LFT_NAME))
A_MLX		= $(addprefix $(DIRS_MLX)/,$(MLX_NAME))

CC			= cc -O3 -ggdb
MLX_FLAGS	= -lXext -lX11 -lz -lm -pthread -ldl -lpthread #-lXfixes #-lasound
CFLAGS		= -Wall -Wextra -Werror -std=c99
OPTION		= -I$(IDIRS) -I$(IDIRS_LFT) -I$(IDIRS_MLX)
MAKEFLAGS 	+= -s
MAKE		= make

all:	$(NAME)

$(ODIRS):
	mkdir -p $(ODIRS)

$(ODIRS)/%.o: $(SDIRS)/%.c $(IFILES) $(IFILES_LFT) $(IFILES_MLX) | $(ODIRS)
	$(CC) $(CFLAGS) $(OPTION) -c $< -o $@

$(A_LFT):
	$(MAKE) -C $(DIRS_LFT)

$(A_MLX):
	$(MAKE) -C $(DIRS_MLX)

$(NAME): $(OFILES) $(A_LFT) $(A_MLX)
	$(CC) -o $(NAME) $(CFLAGS) $(OPTION) $(OFILES) $(A_LFT) $(A_MLX) $(MLX_FLAGS)

$(ODIRS_B):
	@mkdir -p $(ODIRS_B)

$(ODIRS_B)/%.o: $(SDIRS_B)/%.c $(IFILES) $(IFILES_LFT) $(IFILES_MLX) | $(ODIRS_B)
	$(CC) $(CFLAGS) $(OPTION) -c $< -o $@

$(BONUS_NAME): $(OFILES) $(A_LFT) $(A_MLX)
		$(CC) -o $(BONUS_NAME) $(CFLAGS) $(OPTION) $(OFILES) $(A_LFT) $(A_MLX) $(MLX_FLAGS)

clean:
	rm -f $(OFILES) $(OFILES_B)
	@rm -rf $(ODIRS) $(ODIRS_B)
	$(MAKE) -C $(DIRS_LFT) clean
	# $(MAKE) -C $(DIRS_MLX) clean

fclean:	clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	$(MAKE) -C $(DIRS_LFT) fclean

re: fclean all

.PHONY: all fclean clean re test
