
#include "cub3d.h"

int	parse_texture(t_info *info, char **path, const char *id)
{
	int (i) = 0;
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

	int (i) = 0;
	while (info->gnl[i] && ft_isspace(info->gnl[i]))
		i++;
	if (info->gnl[i++] != id)
		return (NULL);
	while (info->gnl[i] && ft_isspace(info->gnl[i]))
		i++;
	int (j) = i - 1;
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

int	parse_color(t_info *info, t_color *color, const char *id)
{
	int (i) = 0;
	while (info->gnl[i] && ft_isspace(info->gnl[i]))
		i++;
	if (info->gnl[i++] != id[0])
		return (2);
	char **(split) = color_split(info, id[0]);
	if (!split)
		return (0);
	char *(s0) = ft_strtrim(split[0], " \n");
	char *(s1) = ft_strtrim(split[1], " \n");
	char *(s2) = ft_strtrim(split[2], " \n");
	if (!s0 || !s1 || !s2)
	{
		free(s0);
		free(s1);
		return (free(s2), ft_tabfree(split), 0);
	}
	int (r) = ft_atoi(s0);
	int (g) = ft_atoi(s1);
	int (b) = ft_atoi(s2);
	ft_tabfree(split);
	free(s0);
	free(s1);
	free(s2);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	color->r = r;
	color->g = g;
	color->b = b;
	info->parsing_nbr++;
	return (1);
}

// if (info->parsing_nbr == i)
// {
// 	if (info->parsing_nbr < 4)
// 	{
// 		if (!parse_texture(info, tex[i], index[i]))
// 			return (ft_printf(2, "Error\nTexture order\n"), 0);
// 	}
// 	else
// 	{
// 		if (!parse_color(info, f_c_colors[i - 4], index[i]))
// 			return (ft_printf(2, "Error\nColor range\n"), 0);
// 	}
// }
// parse_texture() --> return (0) pour strncmp != 0
// color_split() --> return (0) pour id mismatch or split issue
// parse_color() --> retirer les 5 premieres lignes et faire appel a color_split()

int	check_duplicates(t_info *info, t_all *all, int i)
{
	char *index[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	char **tex[4] = {&info->npath, &info->spath, &info->wpath, &info->epath};
	t_color *f_c_colors[2] = {&all->floor, &all->ceiling};
	int *f_c_flags[2] = {&all->df, &all->dc};

	(void) i;
	int ret = 0;
	for (int j = 0; j < 6; j++)
	{
		if (j < 4 && !*tex[j])
		{
			ret = parse_texture(info, tex[j], index[j]);
			if (ret == 1)
				break ;
			else if (ret == 0)
				return (ft_printf(2, "Error\nMalloc\n"), 0);
		}
		else if (j >= 4 && !*f_c_flags[j - 4]) {
			ret = parse_color(info, f_c_colors[j - 4], index[j]);
			if (ret == 1) {
				*f_c_flags[j - 4] = 1;
				break ;
			}
			else if (ret == 0)
				return (ft_printf(2, "Error\nColor range\n"), 0);
		}
	}
	return (1);
}

int	get_tex_mandatory(t_all *all, t_info *info)
{
	info->gnl = ft_get_next_line(info->fd);
	if (!info->gnl)
		return (ft_printf(2, "Error\nplan empty\n"), 0);
	int i = 0;
	while (info->gnl != NULL)
	{
		if (info->parsing_nbr == TEX_NBR)
			break ;
		if (info->gnl[0] != '\n')
		{
			if (i < TEX_NBR) {
				if (!check_duplicates(info, all, i))
					return (0);
			}
			i++;
		}
		free(info->gnl);
		info->gnl = ft_get_next_line(info->fd);
	}
	if (i > TEX_NBR)
		return (ft_printf(2, "Error\nToo much information\n"), 0);
	if (info->parsing_nbr < TEX_NBR)
		return (ft_printf(2, "Error\nSomething's missing\n"), 0);
	return (1);
}