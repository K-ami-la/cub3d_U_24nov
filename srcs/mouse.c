/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaizatov <kaizatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:47:09 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/25 17:17:30 by kaizatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_player *p, double angle)
{
	double	old_dx;
	double	old_planex;

	old_dx = p->dx;
	old_planex = p->planex;
	p->dx = p->dx * cos(angle) - p->dy * sin(angle);
	p->dy = old_dx * sin(angle) + p->dy * cos(angle);
	p->planex = p->planex * cos(angle) - p->planey * sin(angle);
	p->planey = old_planex * sin(angle) + p->planey * cos(angle);
}

// static void	apply_mouse_rotation(t_all *all, int delta_x)
// {
// 	double		rot_speed;
// 	double		angle;
// 	t_player	*p;

// 	p = &all->player;
// 	all->window.mouse.x = (double)delta_x
// 		/ (double)all->window.main_w * 20.0;
// 	rot_speed = 0.006;
// 	angle = all->window.mouse.x * rot_speed;
// 	rotate_player(p, angle);
// }

// int	mouse_move(int x, int y, t_all *all)
// {
// 	int			delta_x;
// 	int			delta_y;

// 	all->window.last_mouse_x = all->window.main_w / 2;
// 	all->window.last_mouse_y = all->window.main_h / 2;
// 	if (x != all->window.last_mouse_x && y != all->window.last_mouse_y)
// 	{
// 		delta_x = x - all->window.last_mouse_x;
// 		delta_y = y - all->window.last_mouse_y;
// 		all->window.mouse.y = (double)delta_y
// 			/ (double)all->window.main_h * 10.0;
// 		apply_mouse_rotation(all, delta_x);
// 		mlx_mouse_move(all->window.mlx, all->window.main,
// 			all->window.main_w / 2, all->window.main_h / 2);
// 	}
// 	return (1);
// }
