/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:54:04 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/20 20:54:43 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void my_mlx_pixel_put(t_game *gm, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= HEIGHT)
		return ;
	mlx_put_pixel(gm->game, x, y, color);
}

static int  get_color(t_game *gm, int flag)
{
	gm->ray.ray_ngl = nor_angle(gm->ray.ray_ngl);
	if (flag == 0)
	{
		if (gm->ray.ray_ngl > M_PI / 2 && gm->ray.ray_ngl < 3 * (M_PI / 2))
			return (0xB5B5B5FF);
		else
			return (0xB5B5B5FF);
	}
	else
	{
		if (gm->ray.ray_ngl > 0 && gm->ray.ray_ngl < M_PI)
			return (0xF5F5F5FF);
		else
			return (0xF5F5F5FF);
	}
}

static float    nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

static void draw_wall(t_game *gm, int ray, int t_pix, int b_pix)
{
	int color;

	color = get_color(gm, gm->ray.flag);
	while (t_pix < b_pix)
		my_mlx_pixel_put(gm, ray, t_pix++, color);
}

static void render_wall(t_game *gm, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	gm->ray.distance *= cos(nor_angle(gm->ray.ray_ngl - gm->cam->angle));
	wall_h = (gm->tile.base / gm->ray.distance) * ((WIDTH / 2) / tan(gm->cam->fov_plr / 2));
	b_pix = (HEIGHT / 2) + (wall_h / 2);
	t_pix = (HEIGHT / 2) - (wall_h / 2);
	if (b_pix > HEIGHT)
		b_pix = HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	draw_wall(gm, ray, t_pix, b_pix);
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
		if (v_inter <= h_inter)
			gm->ray.distance = v_inter;
		else
		{
			gm->ray.distance = h_inter;
			gm->ray.flag = 1;
		}
		render_wall(gm, ray);
		ray++;
		gm->ray.ray_ngl += (gm->cam->fov_plr / WIDTH);
	}
}