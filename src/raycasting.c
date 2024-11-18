/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:56:07 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/14 16:26:08 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int unit_circle(float angle, char c)
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


static int inter_check(float angle, float *inter, float *step, t_game *gm)
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

static int wall_hit(float x, float y, t_game *gm)
{
	int     x_m;
	int     y_m;
    t_map   *map;

    map = gm->map;
	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / gm->tile.base);
	y_m = floor (y / gm->tile.base);
	if ((y_m >= gm->tile.height || x_m >= gm->tile.width))
		return (0);
    while (map)
    {
        if (map->column == y_m && map->line == x_m)
            break ;
        map = map->nxt;
    }
    if (map && map->content == '1')
        return (0);
    return (1);
}

static float get_h_inter(t_game *gm, float angl)
{
	float h_x;
	float h_y;
	float x_step;
	float y_step;
	int  pixel;

	y_step = gm->tile.base;
	x_step = gm->tile.base / tan(angl);
	h_y = floor(gm->cam->plr_y / gm->tile.base) * gm->tile.base;
    gm->is_horizon = 1;
	pixel = inter_check(angl, &h_y, &y_step, gm);
	h_x = gm->cam->plr_x + (h_y - gm->cam->plr_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, gm))
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - gm->cam->plr_x, 2) + pow(h_y - gm->cam->plr_y, 2)));
}

static float get_v_inter(t_game *gm, float angl)
{
	float v_x;
	float v_y;
	float x_step;
	float y_step;
	int  pixel;

	x_step = gm->tile.base; 
	y_step = gm->tile.base * tan(angl);
	v_x = floor(gm->cam->plr_x / gm->tile.base) * gm->tile.base;
    gm->is_horizon = 0;
	pixel = inter_check(angl, &v_x, &x_step, gm);
	v_y = gm->cam->plr_y + (v_x - gm->cam->plr_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, gm))
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - gm->cam->plr_x, 2) + pow(v_y - gm->cam->plr_y, 2)));
}

void cast_rays(t_game *gm)
{
	double h_inter;
	double v_inter;
	int  ray;

	ray = 0;
	gm->ray.ray_ngl = gm->cam->angle - (gm->cam->fov_rd / 2);
	while (ray < WIDTH)
	{
		gm->ray.flag = 0;
		h_inter = get_h_inter(gm, nor_angle(gm->ray.ray_ngl));
		v_inter = get_v_inter(gm, nor_angle(gm->ray.ray_ngl));
		if (v_inter <= h_inter)
			gm->ray.distance = v_inter;
		else
		{
			gm->ray.distance = h_inter;
			gm->ray.flag = 1;
		}
		render_wall(gm, ray);
		ray++;
		gm->ray.ray_ngl += (gm->cam->fov_rd / WIDTH);
	}
}