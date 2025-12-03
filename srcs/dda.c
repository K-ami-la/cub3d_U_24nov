/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaizatov <kaizatov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-03 00:44:39 by kaizatov          #+#    #+#             */
/*   Updated: 2025-12-03 00:44:39 by kaizatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//digital differential analyzer
//dx = cos(angle); dy = sin(angle)
//Wolfenstein ->  different screen coordinate system
//ray tracing = like ray casting but with reflection and shadow
//planX = -dy * FOV ; planY =  dx * FOV
//deltadistX=distance travelled by the ray from one side of the cell to the ..
//fabs: the value should be positive
//mapx is an int = map index
//division par 0 = undefined behaviour
//raydirx=0 the ray doesn't move horizantaly, but strictly vertically
//1e30 = 1 × 10^30
//to know the distance travelled by the ray in one cell= 1.0 (case) / rayon
static void	setup_ray_direction(t_player *p, t_raycasting *r, int w)
{
	r->camerax = 2.0 * r->x / (double)w - 1.0;
	r->raydirx = p->dx + p->planex * r->camerax;
	r->raydiry = p->dy + p->planey * r->camerax;
	r->mapx = (int)p->x;
	r->mapy = (int)p->y;
	if (r->raydirx == 0)
		r->deltadistx = 1e30;
	else
		r->deltadistx = fabs(1.0 / r->raydirx);
	if (r->raydiry == 0)
		r->deltadisty = 1e30;
	else
		r->deltadisty = fabs(1.0 / r->raydiry);
}

//setup the stepx= moves left or right; stepy= moves up or down
//r->sidedistx = (p->x - r->mapx) * r->deltadistx
//we add 1.0 to touch the bord
//site : lodev raycasting 
//!sidedist =distance from the player to the next side
static void	setup_dda_parameters(t_raycasting *r, t_player *p)
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
//goes until there is no wall
//as long as there is no wall and the cell is valid
//r->side = 0; = vertical side

static t_map	*dda_function(t_raycasting *r, t_map *current_cell, char c)
{
	while (!r->hit && current_cell)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			if (r->stepx > 0)
				current_cell = current_cell->right;
			else
				current_cell = current_cell->left;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			if (r->stepy > 0)
				current_cell = current_cell->down;
			else
				current_cell = current_cell->up;
			r->side = 1;
		}
		if (current_cell)
			hit(current_cell, r, c);
	}
	return (current_cell);
}
//fct that determines which texture
//int *s = pointer to the texture
//map_cell->i != '1' if the cell is not a wall. *s = 0 by default
//3=Est; 2=West; 1=North; 0=South
//side=0 (vertical)
//rendering_image(&all->tex.walls[*s], all, r->x, 1.0); draws pixel colon
//all->tex.walls → array of wall textures
//r->x : cuurent colone
//1.0 scale factor > no zoom in /out

static void	select_wall_texture(t_map *map_cell, t_raycasting *r, int *s,
	t_all *all)
{
	if (!map_cell || map_cell->i != '1')
	{
		*s = 0;
		return ;
	}
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

//w = all->window.main_w; the width of the window
//s = wall texture
// current_pos = dda_function(r, current_pos, '1')
//... -> we are searching the wall
// dda_function(r, current_pos, '1'); (to pass the c = 1 = is a wall)
void	raycasting(t_all *all, t_player *p, t_raycasting *r)
{
	int		w;
	int		s;
	t_map	*current_pos;

	w = all->window.main_w;
	r->x = -1;
	while (++r->x < w)
	{
		current_pos = p->h;
		r->hit = false;
		setup_ray_direction(p, r, w);
		setup_dda_parameters(r, p);
		current_pos = dda_function(r, current_pos, '1');
		line_height_calculation(all, r, p);
		render_floor_ceiling(all, r);
		s = 0;
		select_wall_texture(current_pos, r, &s, all);
	}
}
