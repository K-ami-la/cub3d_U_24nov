/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:46:24 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/26 20:13:41 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

static int	engine_game(t_all *all)
{
	movement_handling(all);
	// if (all->movement.move[XK_m])
	// 	minimap(all);
	mlx_put_image_to_window(all->window.mlx, all->window.main,
		all->window.image.img, 0, 0);
	return (1);
}

int	looping(t_all *all)
{
	t_player		*p;
	t_raycasting	*r;
	double			dt;

	p = &all->player;
	r = &all->ray;
	r->x = 0;
	p->ms = 0.2;
	if (++(all->i) - all->frame < (int)(100 / 60))
		return (0);
	all->time = get_current_time();
	dt = all->time - all->oldtime;
	all->oldtime = all->time;
	(void)dt;
	ft_bzero(all->window.image.addr,
		(all->window.main_w * all->window.main_h
			* all->window.image.bits_per_pixel / 8));
	raycasting(all, p, r);
	if (!engine_game(all))
		exit((ft_clearall(all), EXIT_FAILURE));
	return (1);
}

int	launcher(t_all *all)
{
	if (!init_window(all))
		return (0);
	if (!walls_tiles(all, &all->tex))
		return (0);
	if (!hook_handling(all))
		return (0);
	return (1);
}
