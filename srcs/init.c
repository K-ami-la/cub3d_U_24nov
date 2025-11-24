/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:49:10 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/22 20:00:00 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_char(t_all *all, t_info *info)
{
	(void)all;
	(void)info;
	return (1);
}

int	init_window(t_all *all)
{
	all->window.main_w = 1920;
	all->window.main_h = 1080;
	all->window.mlx = mlx_init();
	if (!all->window.mlx)
		return (0);
	all->window.main = mlx_new_window(all->window.mlx,
			all->window.main_w, all->window.main_h, "Cub3D");
	if (!all->window.main)
		return (0);
	all->window.image.img = mlx_new_image(all->window.mlx,
			all->window.main_w, all->window.main_h);
	all->window.image.addr = mlx_get_data_addr(all->window.image.img,
			&all->window.image.bits_per_pixel,
			&all->window.image.line_length, &all->window.image.endian);
	return (1);
}
