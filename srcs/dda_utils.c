/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:41:54 by ulmagner          #+#    #+#             */
/*   Updated: 2025/12/01 20:00:00 by kaizatov        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

//i is the wall
//map_cell can be null if we exit the map
void	hit(t_map *map_cell, t_raycasting *r, char c)
{
	if (map_cell && (map_cell->i == c))
		r->hit = true;
}

static void	trim_newline(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

int	walls_tiles(t_all *all, t_texture *tex)
{
	int	i;

	i = -1;
	tex->walls = malloc(sizeof(t_image) * 4);
	if (!tex->walls)
		return (0);
	trim_newline(all->info.npath);
	trim_newline(all->info.spath);
	trim_newline(all->info.wpath);
	trim_newline(all->info.epath);
	tex->walls[0].img_path = all->info.npath;
	tex->walls[1].img_path = all->info.spath;
	tex->walls[2].img_path = all->info.wpath;
	tex->walls[3].img_path = all->info.epath;
	while (++i < 4)
	{
		if (!create_image(&tex->walls[i], &all->window))
			return (free_walls(tex, all, i), 0);
	}
	return (1);
}

//the fct calculates the line to be displayed
//!!!: tex_x position where the ray touches the wall from 0 t 1
//calculates "perpwalldist" the perpendicular distance to the wall
//lineheight)
// drawstart, drawend
//all->window.main_h : height window
//wall_x -= floor(wall_x);  cause we need decimal value from 0 to 1
//...ex wall=10.73  floor(wall)= 10. 10.73 - 10 = 0.73
//... dans #include <math.h>

void	line_height_calculation(t_all *all, t_raycasting *r, t_player *p)
{
	double	wall_x;

	if (r->side == 0)
		r->perpwalldist = r->sidedistx - r->deltadistx;
	else
		r->perpwalldist = r->sidedisty - r->deltadisty;
	if (r->perpwalldist < 0.1)
		r->perpwalldist = 0.7;
	r->lineheight = (int)(all->window.main_h / r->perpwalldist);
	r->drawstart = -r->lineheight / 2 + all->window.main_h / 2;
	if (r->drawstart < 0)
		r->drawstart = 0;
	r->drawend = r->lineheight / 2 + all->window.main_h / 2;
	if (r->drawend >= all->window.main_h)
		r->drawend = all->window.main_h - 1;
	if (r->side == 0)
		wall_x = p->y + r->perpwalldist * r->raydiry;
	else
		wall_x = p->x + r->perpwalldist * r->raydirx;
	wall_x -= floor(wall_x);
	r->tex_x = wall_x;
}
