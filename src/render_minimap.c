/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:44:12 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/11 17:14:58 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

static void	draw_orientation(mlx_image_t *p_img, t_game *gm, int radius)
{
	double dx = cos(gm->cam->angler);
    double dy = -sin(gm->cam->angler);
	int px = radius;
    int py = radius;
    int i = 0;

	while (i < radius)
    {
        if (px >= 0 && px < gm->tile.base && py >= 0 && py < gm->tile.base)
            mlx_put_pixel(p_img, px, py, 0xFFFFFFFF);
        px += dx;
        py += dy;
        i++;
    }	
}

static void	draw_player(mlx_image_t *p_img, t_game *gm, int radius)
{
	int	x;
	int	y;
	
	x = 0;
	while (x <= gm->tile.base)
	{
		y = 0;
		while (y <= gm->tile.base)
		{
			if (pow(x - radius, 2) + pow(y - radius, 2) <= pow(radius, 2))
				mlx_put_pixel(p_img, x, y, 0x470b23FF);
			y++;
		}
		x++;
	}
	draw_orientation(p_img, gm, radius);
}

static void	put_pixel_minimap(mlx_image_t *img, t_map *ref, int size)
{
	int	i;
	int	j;
	int	size_x;
	int	size_y;

	size_x = (ref->line * size) + size;
	size_y = (ref->column * size) + size;
	j = ref->column * size;
	while (j <= size_y)
	{
		i = ref->line * size;
		while (i <= size_x)
		{
			if (ref->content == '1')
				mlx_put_pixel(img, i, j, 0x03362dFF);
			else
				mlx_put_pixel(img, i, j, 0x858585FF);
			i++;
		}
		j++;
	}

}

void	init_minimap(t_game *gm)
{
	int		base;
	t_map	*map;

	base = gm->tile.base;
	gm->img = mlx_new_image(gm->mlx_on, gm->tile.height * base, gm->tile.width * base);
	if (base > 1)
		gm->p_img = mlx_new_image(gm->mlx_on, base/2, base/2);
	else
		gm->p_img = mlx_new_image(gm->mlx_on, 1, 1);
	map = gm->map;
	while (map)
	{
		put_pixel_minimap(gm->img, map, base);
		map = map->nxt;
	}
	draw_player(gm->p_img, gm, base / 4);
	mlx_image_to_window(gm->mlx_on, gm->img, 0, 0);
	mlx_image_to_window(gm->mlx_on, gm->p_img, gm->cam->plr_x, gm->cam->plr_y);
}
