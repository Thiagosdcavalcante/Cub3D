/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:44:12 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/08 18:43:15 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

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
			if (pow(x - radius, 2) + pow(y - radius, 2) <= pow(radius/2, 2))
				mlx_put_pixel(p_img, x, y, 0x470b23FF);
			y++;
		}
		x++;
	}
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
	gm->p_img = mlx_new_image(gm->mlx_on, base, base);
	map = gm->map;
	while (map)
	{
		put_pixel_minimap(gm->img, map, base);
		map = map->nxt;
	}
	draw_player(gm->p_img, gm, base / 2);
	mlx_image_to_window(gm->mlx_on, gm->img, 0, 0);
	mlx_image_to_window(gm->mlx_on, gm->p_img, gm->cam->player->line * base, gm->cam->player->column * base);
}
