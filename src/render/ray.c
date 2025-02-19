/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:17:12 by tsantana          #+#    #+#             */
/*   Updated: 2025/02/19 15:58:37 by tsantana         ###   ########.fr       */
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
	t_map	*map;

	if (x < 0 || y < 0)
		return (0);
	map = gm->map_position;
	x = (int)floor(x / gm->tile.base); // get the x position in the map
	y = (int)floor(y / gm->tile.base); // get the y position in the map
	if (y > gm->tile.height || x > gm->tile.width)
		return (0);
	while (map && map->down && map->line != y)
		map = map->down;
	while (map && map->nxt && map->column != x)
		map = map->nxt;
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
	h_y = floorf((double)(gm->cam->plr_y / gm->tile.base)) * gm->tile.base;
	gm->is_horizon = unit_circle(angl, 'x');
	pixel = inter_check(angl, &h_y, &y_step, gm);
	h_x = gm->cam->plr_x + (h_y - gm->cam->plr_y) / tan(angl);
	if ((x_step > 0) == unit_circle(angl, 'y'))
		x_step = -x_step;
	while (wall_hit(h_x, h_y - pixel, gm) == 1) // check the wall hit whit the pixel value
	{
		h_x += x_step;
		h_y += y_step;
	}
	gm->ray.info->x = h_x;
	gm->ray.info->y = 0;
	return (pytheorem(pow(h_x - gm->cam->plr_x, 2), pow(h_y - gm->cam->plr_y, 2))); // get the distance
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
	gm->is_horizon = !unit_circle(angl, 'x');
	v_x = floorf(gm->cam->plr_x / gm->tile.base) * gm->tile.base;
	pixel = inter_check(angl, &v_x, &x_step, gm); // check the intersection and get the pixel value
	v_y = gm->cam->plr_y + (v_x - gm->cam->plr_x) * tan(angl);
	if ((y_step < 0) == unit_circle(angl, 'y'))
		y_step = -y_step;
	while (wall_hit(v_x - pixel, v_y, gm) == 1) // check the wall hit whit the pixel value
	{
		v_x += x_step;
		v_y += y_step;
	}
	gm->ray.info->x = 0;
	gm->ray.info->y = v_y;
	return (sqrt(pow(v_x - gm->cam->plr_x, 2) + pow(v_y - gm->cam->plr_y, 2)));
}

void	cast_rays(t_game *gm)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	gm->ray.ray_ngl = gm->cam->angle - (gm->cam->fov_plr / 2);
	while (ray < WIDTH)
	{
		gm->ray.flag = 0;
		h_inter = get_h_inter(gm, nor_angle(gm->ray.ray_ngl));
		v_inter = get_v_inter(gm, nor_angle(gm->ray.ray_ngl));
		if (v_inter < h_inter)
			gm->ray.distance = get_v_inter(gm, nor_angle(gm->ray.ray_ngl));
		else
		{
			gm->ray.distance = get_h_inter(gm, nor_angle(gm->ray.ray_ngl));
			gm->ray.flag = 1;
		}
		render_wall(gm, ray++);
		gm->ray.ray_ngl += ((double) gm->cam->fov_plr / WIDTH);
	}
}