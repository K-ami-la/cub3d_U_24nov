/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_utils.c                                     :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:12:09 by ulmagner          #+#    #+#             */
/*   Updated: 2025/12/01 20:00:00 by kaizatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(t_info *info, char **path, const char *id)
{
	int	i;

	i = 0;
	while (info->gnl[i] && ft_isspace(info->gnl[i]))
		i++;
	if (ft_strncmp(&info->gnl[i], id, ft_strlen(id)) != 0)
		return (2);
	i += ft_strlen(id);
	while (info->gnl[i] && ft_isspace(info->gnl[i]))
		i++;
	*path = ft_strdup(&info->gnl[i]);
	if (!*path)
		return (0);
	info->parsing_nbr++;
	return (1);
}

char	**color_split(t_info *info, char id)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	while (info->gnl[i] && ft_isspace(info->gnl[i]))
		i++;
	if (info->gnl[i++] != id)
		return (NULL);
	while (info->gnl[i] && ft_isspace(info->gnl[i]))
		i++;
	j = i - 1;
	while (info->gnl[++j])
		if (!ft_isdigit(info->gnl[j]) && info->gnl[j] != ','
			&& !ft_isspace(info->gnl[j]))
			return (NULL);
	split = ft_split(info->gnl + i, ',');
	if (!split || ft_countwords(info->gnl + i, ',') != 3)
	{
		if (split)
			ft_tabfree(split);
		return (NULL);
	}
	return (split);
}

static int	process_parsing_loop(t_info *info, t_all *all, int *i)
{
	while (info->gnl != NULL)
	{
		if (info->parsing_nbr == TEX_NBR)
			break ;
		if (info->gnl[0] != '\n')
		{
			if (*i < TEX_NBR)
			{
				if (!check_duplicates(info, all, *i))
					return (0);
			}
			(*i)++;
		}
		free(info->gnl);
		info->gnl = ft_get_next_line(info->fd);
	}
	return (1);
}

int	get_tex_mandatory(t_all *all, t_info *info)
{
	int	i;

	info->gnl = ft_get_next_line(info->fd);
	if (!info->gnl)
		return (ft_printf(2, "Error\nplan empty\n"), 0);
	i = 0;
	if (!process_parsing_loop(info, all, &i))
		return (0);
	if (i > TEX_NBR)
		return (ft_printf(2, "Error\nToo much information\n"), 0);
	if (info->parsing_nbr < TEX_NBR)
		return (ft_printf(2, "Error\nSomething's missing\n"), 0);
	return (1);
}
