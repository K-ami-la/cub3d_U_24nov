/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:21:48 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/22 20:00:00 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_handling(int ac, char **av, t_info *info)
{
	if (ac != 2)
		return (ft_printf(2, "Error\nInvalid number of arguments\n"), 0);
	if (ft_strlen(av[1]) < 4
		|| ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		return (ft_printf(2, "Error\nInvalid file extension\n"), 0);
	info->fd = open(av[1], O_RDONLY);
	if (info->fd < 0)
		return (ft_printf(2, "Error\nfile can't be open\n"), 0);
	return (1);
}
