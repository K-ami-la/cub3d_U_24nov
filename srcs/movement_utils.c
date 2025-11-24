/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:07:51 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/22 20:00:00 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_x(t_player *p, double old_x, double new_x, double dirx)
{
	if (dirx > 0 && p->h->right && p->h->right->i == '1'
		&& new_x >= p->h->x + 1)
		new_x = old_x;
	else if (dirx < 0 && p->h->left && p->h->left->i == '1'
		&& new_x <= p->h->x)
		new_x = old_x;
	return (new_x);
}
