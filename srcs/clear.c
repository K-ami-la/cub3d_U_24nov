/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:33:43 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/22 20:00:00 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_walls(t_texture *tex, t_all *all, int i)
{
	while (--i >= 0)
		mlx_destroy_image(all->window.mlx, tex->walls[i].img);
	free(tex->walls);
	tex->walls = NULL;
}

static void	ft_freewindow(t_window *window)
{
	if (window->image.img)
		mlx_destroy_image(window->mlx, window->image.img);
	if (window->mlx)
	{
		if (window->main)
			mlx_destroy_window(window->mlx, window->main);
		mlx_destroy_display(window->mlx);
		free(window->mlx);
	}
}

static void	ft_freeimage(t_all *all, int i)
{
	int	j;
	int	a;
	int	b;

	b = 0;
	if (all->tex.nbr_image == 0)
		return ;
	while (++i < all->tex.nbr_image)
	{
		j = -1;
		while (++j < all->tex.nbr_i[i])
		{
			a = -1;
			while (++a < all->tex.nbr_a[b])
				mlx_destroy_image(all->window.mlx,
					all->tex.tiles[i][j][a].img);
			b++;
			free(all->tex.tiles[i][j]);
		}
		free(all->tex.tiles[i]);
	}
	free(all->tex.tiles);
}

static void	ft_freewwalls(t_all *all)
{
	int	i;

	i = -1;
	if (!all->tex.walls)
		return ;
	while (++i < 4)
		mlx_destroy_image(all->window.mlx, all->tex.walls[i].img);
	free(all->tex.walls);
	all->tex.walls = NULL;
}

void	ft_clearall(t_all *all)
{
	int	i;

	i = -1;
	ft_freemap(&all->map);
	ft_freeplayer(&all->player);
	ft_freeimage(all, i);
	ft_freewwalls(all);
	ft_freeinfo(&all->info);
	ft_freetex(&all->tex);
	ft_freewindow(&all->window);
	if (all->info.fd != -1)
		close(all->info.fd);
}
