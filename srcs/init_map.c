/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:39:21 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/22 20:00:00 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_info(t_info *info, t_all *all)
{
	if (!get_tex_mandatory(all, info))
		return (0);
	info->map = ft_calloc(1, sizeof(char));
	if (!info->map)
		return (0);
	if (!get_map(info) || !check_ep_doubles(info))
		return (ft_printf(2, "Error\nplanS\n"), 0);
	info->sp_map = ft_split(info->map, '\n');
	if (!info->sp_map)
		return (0);
	info->size_map = ft_strlen(info->map);
	info->column = ft_calloc(info->line, sizeof(int));
	if (!info->column)
		return (0);
	int (i) = -1;
	int (l) = 0;
	while (info->map[++i])
	{
		if (info->map[i] == '\n')
			l++;
		else
			info->column[l]++;
	}
	return (1);
}

static int	fill_map(t_info *info, t_map **head, t_all *all)
{
	t_map	*curr;
	t_map	*node;

	*head = NULL;
	curr = NULL;
	node = NULL;
	info->i_y = -1;
	while (++(info->i_y) < info->line)
	{
		info->i_x = -1;
		while (++(info->i_x) < info->column[info->i_y])
		{
			if (!make_list(&node, all))
				return (0);
			chain_map(&curr, head, node);
			chain_map_updown(node, info, head, &curr);
		}
	}
	if (*head)
	{
		curr->right = NULL;
		(*head)->left = curr;
	}
	return (1);
}

void	print_map(t_map **head, t_info *info)
{
	t_map	*row;
	t_map	*col;
	int		l;

	row = *head;
	l = 0;
	while (row)
	{
		col = row;
		while (col)
		{
			ft_printf(1, "%c", col->i);
			if (col->x == info->column[l] - 1)
				break ;
			col = col->right;
		}
		ft_printf(1, "\n");
		if (l == info->line - 1)
			break ;
		l++;
		row = row->down;
	}
}

int	map_handling(t_info *info, t_map **map, t_all *all)
{
	if (!get_info(info, all))
		return (0);
	if (!init_char(all, info))
		return (0);
	if (!fill_map(info, map, all))
		return (0);
	check_close_map(map, all);
	print_map(map, info);
	return (1);
}
