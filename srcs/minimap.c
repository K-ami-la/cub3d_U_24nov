/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:41:29 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/22 20:00:00 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//aim : draws a square with a given number of pixels on the minimap 
//goes across a grid
//conversion of the color (r << 16) | (g << 8) | b combine RGB 
//... in hexadicimal format example : (ex: red=255 → 0xFF0000)
//draws a pixel at the position (x + x_ref, y + y_ref).
static void	copy_to_minimap(t_window *window, int x_ref,
	int y_ref, t_color *color)
{
	int	c;
	int	x;
	int	y;

	y = -1;
	while (++y < 20)
	{
		x = -1;
		while (++x < 20)
		{
			c = (color->r << 16) | (color->g << 8) | (color->b);
			ft_pixel_put(window, x + x_ref, y + y_ref, c);
		}
	}
}

//assigns a color according to the cell
//sapce = white, wall = black, position of the player Blue
static t_color	assign_color(t_color color, char c, int *x)
{
	*x += 20;
	color = (t_color){254, 254, 254, 254};
	if (c == '1')
		color = (t_color){0, 0, 0, 0};
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		color = (t_color){0, 0, 0, 255};
	return (color);
}

//main function
//goes accross the 2D map and generates the minimap
//the map is a listed chain 2d each knot has a pointer to the right and down
//
void	minimap(t_all *all)
{
	int		x;
	t_map	*col;
	t_color	color;

	int (y) = 0;
	int (l) = 0;
	t_map *(row) = all->map;
	while (row)
	{
		col = row;
		x = -20;
		while (col)
		{
			color = assign_color(color, col->i, &x);
			copy_to_minimap(&all->window, x, y, &color);
			if (col->x == all->info.column[l] - 1)
				break ;
			col = col->right;
		}
		l++;
		y += 20;
		if (col->y == all->info.line)
			break ;
		row = row->down;
	}
}
