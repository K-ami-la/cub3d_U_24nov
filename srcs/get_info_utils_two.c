/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaizatov <kaizatov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-01 17:53:49 by kaizatov          #+#    #+#             */
/*   Updated: 2025-12-01 17:53:49 by kaizatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_rgb(char **split, int *r, int *g, int *b)
{
	char	*s0;
	char	*s1;
	char	*s2;

	s0 = ft_strtrim(split[0], " \n");
	s1 = ft_strtrim(split[1], " \n");
	s2 = ft_strtrim(split[2], " \n");
	if (!s0 || !s1 || !s2)
		return (free(s0), free(s1), free(s2), 0);
	*r = ft_atoi(s0);
	*g = ft_atoi(s1);
	*b = ft_atoi(s2);
	free(s0);
	free(s1);
	free(s2);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (0);
	return (1);
}

int	parse_color(t_info *info, t_color *color, const char *id)
{
	int		i;
	char	**split;
	int		r;
	int		g;
	int		b;

	i = 0;
	while (info->gnl[i] && ft_isspace(info->gnl[i]))
		i++;
	if (info->gnl[i++] != id[0])
		return (2);
	split = color_split(info, id[0]);
	if (!split)
		return (0);
	if (!validate_rgb(split, &r, &g, &b))
		return (ft_tabfree(split), 0);
	ft_tabfree(split);
	color->r = r;
	color->g = g;
	color->b = b;
	info->parsing_nbr++;
	return (1);
}

static int	try_parse_tex(t_info *info, char **tex[4], char *id[6], int i)
{
	int	ret;

	if (i < 4 && !*tex[i])
	{
		ret = parse_texture(info, tex[i], id[i]);
		if (ret == 1)
			return (1);
		if (ret == 0)
			return (ft_printf(2, "Error\nMalloc\n"), 0);
	}
	return (2);
}

static int	try_parse_col(t_info *info, t_all *all, char *id[6], int i)
{
	t_color	*col[2];
	int		*flags[2];
	int		ret;

	col[0] = &all->floor;
	col[1] = &all->ceiling;
	flags[0] = &all->df;
	flags[1] = &all->dc;
	if (i >= 4 && !*flags[i - 4])
	{
		ret = parse_color(info, col[i - 4], id[i]);
		if (ret == 1)
			return (*flags[i - 4] = 1, 1);
		if (ret == 0)
			return (ft_printf(2, "Error\nColor range\n"), 0);
	}
	return (2);
}

int	check_duplicates(t_info *info, t_all *all, int i)
{
	char	*id[6];
	char	**tex[4];
	int		ret;

	(void)i;
	id[0] = "NO";
	id[1] = "SO";
	id[2] = "WE";
	id[3] = "EA";
	id[4] = "F";
	id[5] = "C";
	tex[0] = &info->npath;
	tex[1] = &info->spath;
	tex[2] = &info->wpath;
	tex[3] = &info->epath;
	i = -1;
	while (++i < 6)
	{
		ret = try_parse_tex(info, tex, id, i);
		if (ret != 2)
			return (ret);
		ret = try_parse_col(info, all, id, i);
		if (ret != 2)
			return (ret);
	}
	return (1);
}
