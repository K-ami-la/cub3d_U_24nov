/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaizatov <kaizatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:54:39 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/25 17:17:22 by kaizatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	tile_is_wall(t_map *tmp, int x, int y)
{
	while (tmp)
	{
		if (x > tmp->x)
			tmp = tmp->right;
		else if (x < tmp->x)
			tmp = tmp->left;
		else if (y > tmp->y)
			tmp = tmp->down;
		else if (y < tmp->y)
			tmp = tmp->up;
		if (x == tmp->x && y == tmp->y)
			break ;
	}
	if (tmp && tmp->i == '1')
		return (true);
	return (false);
}

static void	walk(t_player *p, double dirx, double diry)
{
	double	old_x;
	double	old_y;
	double	new_x;
	double	new_y;

	old_x = p->x;
	old_y = p->y;
	new_x = old_x + dirx * p->ms;
	new_y = old_y + diry * p->ms;
	new_x = get_x(p, old_x, new_x, dirx);
	new_y = old_y + diry * p->ms;
	if (diry > 0 && p->h->down && p->h->down->i == '1' && new_y >= p->h->y + 1)
		new_y = old_y;
	else if (diry < 0 && p->h->up && p->h->up->i == '1' && new_y <= p->h->y)
		new_y = old_y;
	if (tile_is_wall(p->h, (int)new_x, (int)new_y))
	{
		p->x = old_x;
		p->y = old_y;
		return ;
	}
	p->x = new_x;
	p->y = new_y;
}

static t_map	*check_height_cases(t_player *player,
	int new_tile_x, int new_tile_y)
{
	t_map *(new_tile) = NULL;
	if (new_tile_y < player->h->y)
		new_tile = player->h->up;
	else if (new_tile_y > player->h->y)
		new_tile = player->h->down;
	if (new_tile_y == player->h->y)
	{
		if (new_tile_x < player->h->x)
			new_tile = player->h->left;
		else if (new_tile_x > player->h->x)
			new_tile = player->h->right;
	}
	else if (new_tile_y != player->h->y && new_tile_x != player->h->x)
	{
		if (new_tile_y < player->h->y && new_tile_x < player->h->x)
			new_tile = player->h->up->left;
		else if (new_tile_y < player->h->y && new_tile_x > player->h->x)
			new_tile = player->h->up->right;
		else if (new_tile_y > player->h->y && new_tile_x < player->h->x)
			new_tile = player->h->down->left;
		else if (new_tile_y > player->h->y && new_tile_x > player->h->x)
			new_tile = player->h->down->right;
	}
	return (new_tile);
}

static void	direction(t_player *player, double dirx, double diry)
{
	t_map	*new_tile;
	char	new_tile_i;
	int		new_tile_x;
	int		new_tile_y;

	new_tile = NULL;
	walk(player, dirx, diry);
	new_tile_x = (int)player->x;
	new_tile_y = (int)player->y;
	if (new_tile_x != (int)player->h->x || new_tile_y != (int)player->h->y)
	{
		new_tile = check_height_cases(player, new_tile_x, new_tile_y);
		if (new_tile && new_tile->i != '1')
		{
			new_tile_i = player->h->i;
			player->h->i = new_tile->i;
			new_tile->i = new_tile_i;
			player->h = new_tile;
		}
	}
}

int	movement_handling(t_all *all)
{
	t_player	*p;
	double		angle;

	p = &all->player;
	angle = 0.05;
	if (all->movement.move[XK_w])
		direction(p, p->dx, p->dy);
	else if (all->movement.move[XK_s])
		direction(p, -p->dx, -p->dy);
	if (all->movement.move[XK_a])
		direction(&all->player, -p->planex, -p->planey);
	else if (all->movement.move[XK_d])
		direction(&all->player, p->planex, p->planey);
	if (all->movement.move[XK_Left])
		rotate_player(p, -angle);
	else if (all->movement.move[XK_Right])
		rotate_player(p, angle);
	return (1);
}
