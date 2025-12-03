/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_utils_three.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaizatov <kaizatov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-02 00:00:00 by kaizatov          #+#    #+#             */
/*   Updated: 2025-12-02 00:00:00 by kaizatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//initialises the arrays for the parsing
//fills the array "id" with identifiers ["NO", "SO","WE","EA", "F", "C"]
//fills the array "tex" with pointers to the textures path
//void return...
//
static void	init_parsing_arrays(t_info *info, char *id[6], char **tex[4])
{
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
}

//parses and avoids the duplicates (NO NO, F F etc.)
//goes over the 6 types of possible info (4 textures + 2 colors)
//for each type tries to parse with try_parse_tex or try_parse_col
//returns 1 = success, 0 error
int	check_duplicates(t_info *info, t_all *all, int i)
{
	char	*id[6];
	char	**tex[4];
	int		ret;

	init_parsing_arrays(info, id, tex);
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

//main function
//coordinates all the parsing
//reads the first file line
//call the process_parsing_loop to parse each line
//check that we have all required infos (6 in total)
//return 1 = success, 0 = error.
//error messages : empty file or too much lines or textures and colors missing
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
