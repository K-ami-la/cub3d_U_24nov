/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:34:42 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/23 23:00:00 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
