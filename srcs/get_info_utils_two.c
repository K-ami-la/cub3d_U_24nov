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

//validates and converts the RGB values
//trims the spaces ans newlines of each element
//converts the strings in int with ft_atoi
//check that each value is between 0 and 255
//stocks the values in r g and b
//returns 1 (valid) and 0 (not valid)
//example: "220, "100é, "0" -> r=220, g=100, b=0
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

//parses a complete line of colors(Floor or Ceiling)
//checks if the line beginns with F or C
//calls the color_split to cut the values
//call validate_rgb to validate and convert
//stocks the RGB values in the structure "color"
//incrementation of parsing_nbr
//returns 1 success and 0 error, 2 not the good line
//Example F 200, 100, 0 > color->r=220; color->g=100, color->b=0
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

//tries to parse the texture if not already defined
//checks if "i" is a texture (0-3 for NO/SO/WE/EA)
//checks if this texxture wasn't already defined
//calls the parse_texture to extract the path
//return 1 success, 0 error, 2 not applicable
int	try_parse_tex(t_info *info, char **tex[4], char *id[6], int i)
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

//parses a color if not defined
//checks if this colors wasnt alreadu defined (flags df ans dc)
//calls the parse_color to exctract the values RGB
//activates the corresponding flag 
//returns 1 success, 0 error, 2 not applicable
int	try_parse_col(t_info *info, t_all *all, char *id[6], int i)
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
