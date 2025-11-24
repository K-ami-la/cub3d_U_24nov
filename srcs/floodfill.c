/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:19:39 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/22 20:00:00 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_invalid_tile(char c)
{
	if (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (1);
}

static void	floodfill(t_map *player, t_all *all)
{
	if ((player->up && is_invalid_tile(player->up->i))
		|| (player->down && is_invalid_tile(player->down->i))
		|| (player->left && is_invalid_tile(player->left->i))
		|| (player->right && player->x < player->right->x
			&& is_invalid_tile(player->right->i))
		|| !player->up || !player->down || !player->left
		|| (player->right && player->x > player->right->x))
	{
		ft_printf(2, "Error\nInvalid map: not closed\n");
		exit((ft_clearall(all), EXIT_FAILURE));
	}
}

static void	get_cam(t_map *curr, t_all *all)
{
	if (curr->i == 'E')
	{
		all->player.dx = -1;
		all->player.dy = 0;
	}
	if (curr->i == 'W')
	{
		all->player.dx = 1;
		all->player.dy = 0;
	}
	if (curr->i == 'N')
	{
		all->player.dx = 0;
		all->player.dy = -1;
	}
	if (curr->i == 'S')
	{
		all->player.dx = 0;
		all->player.dy = 1;
	}
	all->player.planex = -all->player.dy * 0.66;
	all->player.planey = all->player.dx * 0.66;
}

void	check_close_map(t_map **map, t_all *all)
{
	t_map	*col;
	t_map	*row;
	int		l;

	row = *map;
	l = 0;
	while (row)
	{
		col = row;
		while (col)
		{
			if (col->i == '0')
				floodfill(col, all);
			if (col->i == 'N' || col->i == 'S'
				|| col->i == 'W' || col->i == 'E')
				get_cam(col, all);
			if (col->x == all->info.column[l] - 1)
				break ;
			col = col->right;
		}
		if (l == all->info.line - 1)
			break ;
		l++;
		row = row->down;
	}
}
