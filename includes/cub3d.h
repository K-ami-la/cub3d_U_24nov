/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:22:35 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/26 20:16:36 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <math.h>
# include <sys/time.h>
# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>

# define TILE_SIZE 64
# define TEX_NBR 6

typedef struct s_map
{
	char			i;
	double			x;
	double			y;
	int				x_pxl;
	int				y_pxl;
	int				is_visited;
	struct s_map	*right;
	struct s_map	*left;
	struct s_map	*up;
	struct s_map	*down;
	struct s_map	*player;
}	t_map;

typedef struct s_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_info
{
	int		i_x;
	int		i_y;
	int		size_map;
	int		*column;
	int		line;
	int		fd;
	int		parsing_nbr;
	char	*map;
	char	**sp_map;
	char	*npath;
	char	*spath;
	char	*wpath;
	char	*epath;
	char	*gnl;
}	t_info;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*img_path;
	int		w;
	int		h;
}	t_image;

typedef struct s_player
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	planex;
	double	planey;
	double	ms;
	t_map	*h;
}	t_player;

typedef struct s_mouse
{
	double	x;
	double	y;
}	t_mouse;

typedef struct s_window
{
	void	*mlx;
	void	*main;
	int		main_w;
	int		main_h;
	t_image	image;
	t_mouse	mouse;
	int		last_mouse_x;
	int		last_mouse_y;
}	t_window;

typedef struct s_raycasting
{
	int		x;
	int		y;
	double	tex_x;
	int		mapx;
	int		mapy;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	bool	hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
}	t_raycasting;

typedef struct s_movement
{
	bool	move[65535];
	int		keycode;
}	t_movement;

typedef struct s_fail
{
	int	a;
	int	b;
	int	k;
	int	j;
	int	i;
}	t_fail;

typedef struct s_texture
{
	// int		*nbr_a;
	// int		*nbr_i;
	// int		nbr_image;
	// char	**path_texture;
	// t_image	***tiles;
	t_image	*walls;
	// t_fail	fail;
}	t_texture;

typedef struct s_all
{
	t_window		window;
	t_info			info;
	t_player		player;
	t_map			*map;
	t_raycasting	ray;
	t_color			argb;
	t_image			image;
	t_movement		movement;
	t_texture		tex;
	t_color			floor;
	t_color			ceiling;
	int				i;
	int				frame;
	int				step;
	int				ac;
	char			**av;
	double			time;
	double			oldtime;
	double			zbuffer[1920];
	int				df;
	int				dc;
}	t_all;

void			rotate_player(t_player *p, double angle);
void			free_walls(t_texture *tex, t_all *all, int i);
int				create_image(t_image *image, t_window *window);
int				ft_isspace(char c);
int				walls_tiles(t_all *all, t_texture *tex);
int				get_tex_mandatory(t_all *all, t_info *info);
double			get_x(t_player *p, double old_x, double new_x, double dirx);
void			line_height_calculation(t_all *all, t_raycasting *r,
					t_player *p);
void			hit(t_map *tmp, t_raycasting *r, t_all *all, char c);
int				init_window(t_all *all);
int				init_char(t_all *all, t_info *info);
// int				mouse_move(int x, int y, t_all *all);
void			minimap(t_all *all);
void			raycasting(t_all *all, t_player *p, t_raycasting *r);
int				hook_handling(t_all *all);
int				looping(t_all *all);
// void			floor_ceiling_raycasting(t_all *all, t_raycasting *r,
// 					t_map *cp, t_player *p);
void			rendering_image(t_image *tex, t_all *all, int xscreen,
					double scale);
t_map			*get_node_at(t_map *head, int x, int y);
// int				split_tile(t_texture *tex, t_all *all);
int				movement_handling(t_all *all);
void			ft_pixel_put(t_window *window, int x, int y, int color);
unsigned int	get_pixel_color(t_image *image, int x, int y);
int				launcher(t_all *all);
int				error_handling(int ac, char **av, t_info *info);
int				get_map(t_info *info);
int				check_ep_doubles(t_info *info);
// void			ft_freetex(t_texture *tex);
void			ft_clearall(t_all *all);
void			ft_freeplayer(t_player *player);
void			ft_freeinfo(t_info *info);
void			ft_tabfree(char **tab);
void			ft_freemap(t_map **map);
void			check_close_map(t_map **map, t_all *all);
void			chain_map(t_map **curr, t_map **head, t_map *node);
void			chain_map_updown(t_map *node, t_info *info,
					t_map **head, t_map **curr);
int				make_list(t_map **node, t_all *all);
void			print_map(t_map **head, t_info *info);
int				map_handling(t_info *info, t_map **map, t_all *all);
void			render_floor_ceiling(t_all *all, t_raycasting *r);

#endif
