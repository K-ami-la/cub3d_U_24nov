/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaizatov <kaizatov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-02 21:33:14 by kaizatov          #+#    #+#             */
/*   Updated: 2025-12-02 21:33:14 by kaizatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//two varibales to store colors in 0xRRGGBB format
//...and a counter for the vertical pixels
//color_ceiling : converts the components R G B (0-255)
//... into a single 13 bit value (for the minilbx)
//while(y < r->drawstart) draw the ceiling
//... from the top to the start of the wall (drawstart))
//ft_pixel_put : draws one pixel in each column
// y : y= 0 first colon, y = 1  second colon. from the top
//while(y < all-> window.main_h). we start from the drawend (end of the wall)
//...until the end of the screen
void	render_floor_ceiling(t_all *all, t_raycasting *r)
{
	unsigned int	color_floor;
	unsigned int	color_ceiling;
	int				y;

	color_ceiling = (all->ceiling.r << 16) | (all->ceiling.g << 8)
		| all->ceiling.b;
	y = 0;
	while (y < r->drawstart)
	{
		ft_pixel_put(&all->window, r->x, y, color_ceiling);
		y++;
	}
	color_floor = (all->floor.r << 16) | (all->floor.g << 8) | all->floor.b;
	y = r->drawend + 1;
	while (y < all->window.main_h)
	{
		ft_pixel_put(&all->window, r->x, y, color_floor);
		y++;
	}
}
