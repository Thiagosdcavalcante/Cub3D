/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:39:14 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/22 17:41:10 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	inter_check(float angle, float *inter, float *step, t_game *gm)	// check the intersection
{
	if (gm->is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += gm->tile.base;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
		{
			*inter += gm->tile.base;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_game *gm)	// check the wall hit
{
	int		x_m;
	int		y_m;
	t_map	*map;

	if (x < 0 || y < 0)
		return (0);
	map = gm->map;
	x_m = floor (x / gm->tile.base); // get the x position in the map
	y_m = floor (y / gm->tile.base); // get the y position in the map
	if ((y_m >= gm->tile.height || x_m >= gm->tile.width))
		return (0);
	while (map)
	{
		if (map->column == x_m && map->line == y_m)
			break ;
		map = map->nxt;
	}
	if (map->content == '1')
		return (0);
	return (1);
}

float	get_h_inter(t_game *gm, float angl)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = gm->tile.base;
	x_step = gm->tile.base / tan(angl);
	h_y = floor(gm->cam->plr_y / gm->tile.base) * gm->tile.base;
	pixel = inter_check(angl, &h_y, &y_step, gm);
	h_x = gm->cam->plr_x + (h_y - gm->cam->plr_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, gm)) // check the wall hit whit the pixel value
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - gm->cam->plr_x, 2) + pow(h_y - gm->cam->plr_y, 2))); // get the distance
}

float	get_v_inter(t_game *gm, float angl)	// get the vertical intersection
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = gm->tile.base; 
	y_step = gm->tile.base * tan(angl);
	v_x = floor(gm->cam->plr_x / gm->tile.base) * gm->tile.base;
	pixel = inter_check(angl, &v_x, &x_step, gm); // check the intersection and get the pixel value
	v_y = gm->cam->plr_y + (v_x - gm->cam->plr_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0)) // check y_step value
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, gm)) // check the wall hit whit the pixel value
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - gm->cam->plr_x, 2) + pow(v_y - gm->cam->plr_y, 2))); // get the distance
}

// void	cast_rays(t_game *gm)	// cast the rays
// {
// 	double	h_inter;
// 	double	v_inter;
// 	int		ray;

// 	ray = 0;
// 	gm->ray.ray_ngl = gm->cam->angle - (gm->cam->fov_plr / 2); // the start angle
// 	while (ray < WIDTH) // loop for the rays
// 	{
// 		gm->ray.flag = 0; // flag for the wall
// 		h_inter = get_h_inter(gm, nor_angle(gm->ray.ray_ngl)); // get the horizontal intersection
// 		v_inter = get_v_inter(gm, nor_angle(gm->ray.ray_ngl)); // get the vertical intersection
// 		if (v_inter <= h_inter) // check the distance
// 			gm->ray.distance = v_inter; // get the distance
// 		else
// 		{
// 			gm->ray.distance = h_inter; // get the distance
// 			gm->ray.flag = 1; // flag for the wall
// 		}
// 		render_wall(gm, ray); // render the wall
// 		ray++; // next ray
// 		gm->ray.ray_ngl += (gm->cam->fov_plr / WIDTH); // next angle
// 	}
// }