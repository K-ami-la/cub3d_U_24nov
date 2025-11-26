/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:35:34 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/26 20:14:10 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_tabfree(char **tab)
{
	int	i;

	i = -1;
	if (!tab || !*tab)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	ft_freemap(t_map **map)
{
	t_map	*head;
	t_map	*curr;
	t_map	*next;

	if (!*map || !map)
		return ;
	head = *map;
	curr = head;
	while (curr != NULL)
	{
		next = curr->right;
		free(curr);
		curr = next;
		if (curr == head)
			break ;
	}
	*map = NULL;
}

void	ft_freeinfo(t_info *info)
{
	if (info->column)
		free(info->column);
	if (info->map)
		free(info->map);
	if (info->sp_map)
		ft_tabfree(info->sp_map);
	if (info->npath)
		free(info->npath);
	if (info->spath)
		free(info->spath);
	if (info->wpath)
		free(info->wpath);
	if (info->epath)
		free(info->epath);
	if (info->gnl)
		free(info->gnl);
}

void	ft_freeplayer(t_player *player)
{
	(void)player;
}

// void	ft_freetex(t_texture *tex)
// {
// 	if (tex->nbr_i)
// 		free(tex->nbr_i);
// 	if (tex->nbr_a)
// 		free(tex->nbr_a);
// 	if (tex->path_texture)
// 		ft_tabfree(tex->path_texture);
// }
