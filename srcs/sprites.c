/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaizatov <kaizatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 23:15:58 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/25 15:40:31 by kaizatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_sprite_params(t_all *all, t_image *tex, double scale,
int *params)
{
	t_raycasting	*r;

	r = &all->ray;
	params[0] = (int)(r->tex_x * (double)tex->w);
	if ((r->side == 0 && r->raydirx < 0) || (r->side == 1 && r->raydiry > 0))
		params[0] = tex->w - params[0] - 1;
	params[1] = (int)(r->lineheight * scale);
	params[2] = all->window.main_h / 2 - params[1] / 2;
	params[3] = params[2] + params[1];
}

static void	draw_sprite_column(t_all *all, t_image *tex, int xscreen,
int *params)
{
	int		color;
	int		col_tex_y;
	double	step;
	double	tex_pos;
	int		y;

	step = 1.0 * tex->h / params[1];
	tex_pos = (all->window.main_h / 2 - params[1] / 2
			- all->window.main_h / 2 + all->ray.lineheight / 2) * step;
	y = params[2] - 1;
	while (++y < params[3])
	{
		col_tex_y = (int)tex_pos & (tex->w - 1);
		tex_pos += step;
		color = get_pixel_color(tex, params[0], col_tex_y);
		if ((color & 0x00FFFFFF) == 0)
			continue ;
		ft_pixel_put(&all->window, xscreen, y, color);
	}
}

//takes the wall texture and selects the pixel colon according to the tex_x
//t_image  *tex = texture; int xscreen = column of the screen
//double scale = to adjust the image
//r = &all->ray; = curent ray
//tex_x = horizontal position in the texture of the ray(from 0 to 1)
//if negative we ignore
//params[0] cordinates of the texture
//parm[1] the start position of th vertical line
//parm[2] the end of the column
//param[3] hight of the column
void	rendering_image(t_image *tex, t_all *all, int xscreen, double scale)
{
	int				params[4];
	t_raycasting	*r;

	r = &all->ray;
	params[0] = (int)(r->tex_x * (double)tex->w);
	if (params[0] < 0)
		return ;
	init_sprite_params(all, tex, scale, params);
	draw_sprite_column(all, tex, xscreen, params);
}
