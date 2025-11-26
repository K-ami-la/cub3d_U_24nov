/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tileset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:24:23 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/26 20:17:11 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_image(t_image *image, t_window *window)
{
	image->img = mlx_xpm_file_to_image(window->mlx,
			image->img_path, &image->w, &image->h);
	if (!image->img)
		return (ft_printf(2, "Error\nTexture path invalid\n"), 0);
	image->addr = mlx_get_data_addr(image->img,
			&image->bits_per_pixel, &image->line_length, &image->endian);
	if (!image->addr)
		return (0);
	return (1);
}

// static int	free_rest(t_texture *tex, t_all *all)
// {
// 	while (--(tex->fail.i) >= 0)
// 	{
// 		tex->fail.j = all->tex.nbr_i[tex->fail.i];
// 		while (--(tex->fail.j) >= 0)
// 		{
// 			tex->fail.a = all->tex.nbr_a[--(tex->fail.b)];
// 			while (--(tex->fail.a) >= 0)
// 			{
// 				if (mlx_destroy_image(all->window.mlx,
// 						tex->tiles[tex->fail.i][tex->fail.j][tex->fail.a].img)
// 					< 0)
// 					return (0);
// 			}
// 			free(tex->tiles[tex->fail.i][tex->fail.j]);
// 		}
// 		free(tex->tiles[tex->fail.i]);
// 	}
// 	if (tex->tiles)
// 	{
// 		free(tex->tiles);
// 		tex->tiles = NULL;
// 	}
// 	return (0);
// }

// static int	free_failedimage(t_texture *tex, t_all *all)
// {
// 	while (--(tex->fail.a) >= 0)
// 	{
// 		if (mlx_destroy_image(all->window.mlx,
// 				tex->tiles[tex->fail.i][tex->fail.j][tex->fail.a].img) < 0)
// 			return (0);
// 	}
// 	if (tex->tiles[tex->fail.i][tex->fail.j])
// 		free(tex->tiles[tex->fail.i][tex->fail.j]);
// 	while (--(tex->fail.j) >= 0)
// 	{
// 		tex->fail.a = all->tex.nbr_a[--(tex->fail.b)];
// 		while (--(tex->fail.a) >= 0)
// 		{
// 			if (mlx_destroy_image(all->window.mlx,
// 					tex->tiles[tex->fail.i][tex->fail.j][tex->fail.a].img) < 0)
// 				return (0);
// 		}
// 		free(tex->tiles[tex->fail.i][tex->fail.j]);
// 	}
// 	if (tex->tiles[tex->fail.i])
// 		free(tex->tiles[tex->fail.i]);
// 	return (free_rest(tex, all));
// }

// static int	spliting_anim(t_texture *tex, t_all *all)
// {
// 	tex->fail.a = -1;
// 	tex->tiles[tex->fail.i][tex->fail.j] = malloc(sizeof(t_image)
// 			* tex->nbr_a[++(tex->fail.b)]);
// 	if (!tex->tiles[tex->fail.i][tex->fail.j])
// 		return (0);
// 	while (++(tex->fail.a) < tex->nbr_a[tex->fail.b])
// 	{
// 		tex->tiles[tex->fail.i][tex->fail.j][tex->fail.a].img_path
// 			= tex->path_texture[++(tex->fail.k)];
// 		if (!create_image(&tex->tiles[tex->fail.i][tex->fail.j][tex->fail.a],
// 				&all->window))
// 			return (0);
// 	}
// 	return (1);
// }

// int	split_tile(t_texture *tex, t_all *all)
// {
// 	tex->fail.i = -1;
// 	tex->fail.k = -1;
// 	tex->fail.b = -1;
// 	tex->tiles = malloc(sizeof(t_image **) * tex->nbr_image);
// 	if (!tex->tiles)
// 		return (free_failedimage(tex, all));
// 	while (++(tex->fail.i) < tex->nbr_image)
// 	{
// 		tex->fail.j = -1;
// 		tex->tiles[tex->fail.i] = malloc(sizeof(t_image *)
// 				* tex->nbr_i[tex->fail.i]);
// 		if (!tex->tiles[tex->fail.i])
// 			return (free_failedimage(tex, all));
// 		while (++(tex->fail.j) < tex->nbr_i[tex->fail.i])
// 		{
// 			if (!spliting_anim(tex, all))
// 				return (free_failedimage(tex, all));
// 		}
// 	}
// 	return (1);
// }
