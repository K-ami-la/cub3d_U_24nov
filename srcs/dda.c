/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:03:28 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/22 20:00:00 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_playerpos_and_fov(t_player *p, t_raycasting *r, int w)
{
	r->camerax = 2.0 * r->x / (double)w - 1.0;
	r->raydirx = p->dx + p->planex * r->camerax;
	r->raydiry = p->dy + p->planey * r->camerax;
	r->mapx = (int)p->x;
	r->mapy = (int)p->y;
	r->deltadistx = fabs(1.0 / r->raydirx);
	r->deltadisty = fabs(1.0 / r->raydiry);
}

static void	init_dda(t_raycasting *r, t_player *p)
{
	if (r->raydirx < 0)
	{
		r->stepx = -1;
		r->sidedistx = (p->x - r->mapx) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->mapx + 1.0 - p->x) * r->deltadistx;
	}
	if (r->raydiry < 0)
	{
		r->stepy = -1;
		r->sidedisty = (p->y - r->mapy) * r->deltadisty;
	}
	else
	{
		r->stepy = 1;
		r->sidedisty = (r->mapy + 1.0 - p->y) * r->deltadisty;
	}
}

static t_map	*dda_function(t_raycasting *r, t_map *tmp, char c, t_all *all)
{
	(void)all;
	while (!r->hit && tmp)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			if (r->stepx > 0)
				tmp = tmp->right;
			else
				tmp = tmp->left;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			if (r->stepy > 0)
				tmp = tmp->down;
			else
				tmp = tmp->up;
			r->side = 1;
		}
		hit(tmp, r, all, c);
	}
	return (tmp);
}

static void	p_wall(t_map *cp, t_raycasting *r, int *s, t_all *all)
{
	if (!cp || cp->i != '1')
		return ;
	if (r->side == 0)
	{
		if (r->raydirx > 0)
			*s = 3;
		else
			*s = 2;
	}
	else
	{
		if (r->raydiry > 0)
			*s = 1;
		else
			*s = 0;
	}
	rendering_image(&all->tex.walls[*s], all, r->x, 1.0);
}

void	raycasting(t_all *all, t_player *p, t_raycasting *r)
{
	int		w;
	int		s;
	t_map	*cp;

	w = all->window.main_w;
	s = 0;
	cp = p->h;
	r->x = 0;
	while (r->x < w)
	{
		cp = p->h;
		r->hit = false;
		set_playerpos_and_fov(p, r, w);
		init_dda(r, p);
		cp = dda_function(r, cp, '1', all);
		line_height_calculation(all, r, p);
		all->zbuffer[r->x] = r->perpwalldist;
		render_floor_ceiling(all, r);
		p_wall(cp, r, &s, all);
		r->y = r->drawend + 1;
		r->x++;
	}
}
