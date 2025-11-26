/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:14:21 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/26 15:52:46 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_ep_doubles(t_info *info)
{
	int	i;
	int	p;

	p = 0;
	i = -1;
	while (info->map[++i])
	{
		if (info->map[i] == 'N' || info->map[i] == 'S'
			|| info->map[i] == 'E' || info->map[i] == 'W')
			p++;
	}
	if (p > 1 || !p)
		return (0);
	return (1);
}

int	get_map(t_info *info)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	while (info->gnl != NULL)
	{
		i = -1;
		while (info->gnl[++i])
		{
			if (!ft_isstrchr("01NSEW \n", info->gnl[i]))
				return (ft_printf(2, "Error\nInvalid character in map\n"), 0);
		}
		if (info->gnl[0] != '\n')
		{
			tmp = ft_strjoin(info->map, info->gnl);
			if (!tmp)
				return (0);
			free(info->map);
			info->map = tmp;
			info->line++;
		}
		free(info->gnl);
		info->gnl = ft_get_next_line(info->fd);
	}
	return (1);
}
