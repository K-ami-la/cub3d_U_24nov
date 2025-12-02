/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaizatov <kaizatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:46:24 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/25 17:16:40 by kaizatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	movement_p(int keycode, t_all *all)
{
	all->movement.move[keycode] = true;
	if (keycode == XK_Escape)
		exit((ft_clearall(all), EXIT_SUCCESS));
	return (0);
}

static int	movement_r(int keycode, t_all *all)
{
	all->movement.move[keycode] = false;
	return (0);
}

static int	close_window(t_all *all)
{
	return (exit((ft_clearall(all), EXIT_FAILURE)), 0);
}

int	hook_handling(t_all *all)
{
	mlx_hook(all->window.main, 2, 1L << 0, movement_p, all);
	mlx_hook(all->window.main, 3, 1L << 1, movement_r, all);
	mlx_hook(all->window.main, 17, 1L << 17, close_window, all);
	mlx_loop_hook(all->window.mlx, looping, all);
	mlx_loop(all->window.mlx);
	return (1);
}
