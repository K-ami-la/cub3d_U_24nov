/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaizatov <kaizatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:03:28 by ulmagner          #+#    #+#             */
/*   Updated: 2025/11/25 17:27:34 by kaizatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//digital differential analyzer
//dx = cos(angle); dy = sin(angle)
//Wolfenstein -> systeme de coordonnées des écrans différent
//ray tracing = like ray casting but with reflection and shadow
//planX = -dy * FOV ; planY =  dx * FOV
//deltadistX = distance que le rayon parcourt pour passer d’une ligne verticale à la suivante
//fabs: la valeur doit etre positive
//mapx est un int = indice de la map
//division par 0 = comportement indéfini
//1e30 = 1 × 10^30
//pour connaitre la distance que le rayon doit parcourir dans une case il faut diviser 1.0 (case) / rayon
static void	setup_ray_direction(t_player *p, t_raycasting *r, int w)
{
	r->camerax = 2.0 * r->x / (double)w - 1.0;
	r->raydirx = p->dx + p->planex * r->camerax;
	r->raydiry = p->dy + p->planey * r->camerax;
	r->mapx = (int)p->x;
	r->mapy = (int)p->y;
	if (r->raydirx == 0)
		r->deltadistx = 1e30;
	else
		r->deltadistx = fabs(1.0 / r->raydirx);
	if (r->raydiry == 0)
		r->deltadisty = 1e30;
	else
		r->deltadisty = fabs(1.0 / r->raydiry);
}

//setup the stepx= avancer vers gauche ou droite; stepy avancer vers haut ou bas.
//r->sidedistx = (p->x - r->mapx) * r->deltadistx; : x - map * largeur d une case
//on rajoute le 1.0 quand c est positif pour atteindre le bord
//site : lodev raycasting 
//!!!sidedist : distance depuis le joueur jusq prochain côé touché
static void	setup_dda_parameters(t_raycasting *r, t_player *p)
{
	if (r->raydirx < 0)
	{
		r->stepx = -1;
		r->sidedistx = (p->x - r->mapx) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->mapx + 1.0 - p->x) * r->deltadistx;
	}
	if (r->raydiry < 0)
	{
		r->stepy = -1;
		r->sidedisty = (p->y - r->mapy) * r->deltadisty;
	}
	else
	{
		r->stepy = 1;
		r->sidedisty = (r->mapy + 1.0 - p->y) * r->deltadisty;
	}
}
//!!!retourn la case ou le rayon a frappé???
//la fonction retourne un pointeur vers la cellule de la grille que le rayon a frappé?
//la cellule ou le rayon commence : t_map *current_cell
//tant que le rayon n'a pas frappé de mur et le cellule est valide
//r->side = 0; on note que le rayon a touche un cote verticale side = 0
//if (current_cell) : on verifie si la cellule actuelle a touché un mur, si oui hit=1
static t_map	*dda_function(t_raycasting *r, t_map *current_cell, char c)
{
	while (!r->hit && current_cell)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			if (r->stepx > 0)
				current_cell = current_cell->right;
			else
				current_cell = current_cell->left;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			if (r->stepy > 0)
				current_cell = current_cell->down;
			else
				current_cell = current_cell->up;
			r->side = 1;
		}
		if (current_cell) 
			hit(current_cell, r, c);
	}
	return (current_cell);
}

//fct pour determiner quel mur dessiner et avec quelle structure puis appelle le rendu
//int * s pointe vrs un entier qui servira à choisir la texture du mur
//map_cell->i != '1' la cellule n'est pas un mur. on met *s par defaut(0)
//3=Est; 2=West; 1=North; 0=South
//side=0 (vertical)
//rendering_image(&all->tex.walls[*s], all, r->x, 1.0); dessiner la colonne en pixels
//all->tex.walls → c’est un tableau de textures de murs.
//*s → l’index de la texture à utiliser (0 à 3 selon la face du mur).
//r->x : la colonne actuelle
//1.0 facteur d'échelle >> pas de zoom pas de reduction ici donc
static void	select_wall_texture(t_map *map_cell, t_raycasting *r, int *s, t_all *all)
{
	if (!map_cell || map_cell->i != '1')
	{
		*s = 0;
		return ;
	}
	if (r->side == 0)
	{
		if (r->raydirx > 0)
			*s = 3;
		else
			*s = 2;
	}
	else
	{
		if (r->raydiry > 0)
			*s = 1;
		else
			*s = 0;
	}
	rendering_image(&all->tex.walls[*s], all, r->x, 1.0);
}

//w = all->window.main_w; on recupère la largeur de la fenêtre
// current_pos = dda_function(r, current_pos, '1'); -> on cherche un mur
void	raycasting(t_all *all, t_player *p, t_raycasting *r)
{
	int		w;
	int		s;
	t_map	*current_pos;

	w = all->window.main_w;
	r->x = -1;
	while (++r->x < w)
	{
		current_pos = p->h;
		r->hit = false;
		setup_ray_direction(p, r, w);
		setup_dda_parameters(r, p);
		current_pos = dda_function(r, current_pos, '1');
		line_height_calculation(all, r, p);
		render_floor_ceiling(all, r);
		s = 0;
		select_wall_texture(current_pos, r, &s, all);
	}
}
