/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:26:50 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/11 20:26:53 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

// static t_map	*find_position(int x, int y, t_map *map, int base)
// {
// 	t_map	*ref;
// 	int		column;
	
// 	ref = map;
// 	column = 0;
// 	while (ref)
// 	{
// 		if (ref->column <= y && ref->column <= ref->column + base - 1)
// 		{
// 			column = ref->column;
// 			break ;
// 		}
// 	}
// 	ref = map;
// 	while (ref && (ref->line <= x && ref->line <= ref->line + base - 1))
// 	{
// 		if (ref->column == column)
// 			return (ref);
// 		ref = ref->nxt;
// 	}
// 	return (NULL);
// }

// static int	colision_control(t_game *gm, int x, int y)
// {
// 	t_map	*ref;
	
// 	ref = find_position(x, y, gm->map, gm->tile.base);
// 	if (ref->content == '1')
// 		return (1);
// 	return (0);
// }

static int	control_map_limits(t_game *gm, int x, int y)
{
	t_map	*map;
	
	map = gm->map;
	x /= gm->tile.base;
	y /= gm->tile.base;
	while (map)
	{
		printf("map->line: %d map->column: %d\n", map->line, map->column);
		if (map->line == x && map->column == y)
			break ;
		map = map->nxt;
	}
	printf("%c\n", map->content);
	if (map->content == '1')
		return (0);
	return (1);
}

void	control_hooks(mlx_key_data_t keydata, void *param)
{
	t_game	*infor;
	
	infor = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(infor->mlx_on);
	else if (keydata.key == MLX_KEY_W)
	{
		if (control_map_limits(infor, infor->p_img->instances->x, infor->p_img->instances->y - 5) == 1)
			infor->p_img->instances->y -= 5;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		if (control_map_limits(infor, infor->p_img->instances->x, infor->p_img->instances->y + 5 + (infor->tile.base / 2)) == 1)
			infor->p_img->instances->y += 5;
	}
	else if (keydata.key == MLX_KEY_A)
	{
		if (control_map_limits(infor, infor->p_img->instances->x - 5, infor->p_img->instances->y) == 1)
			infor->p_img->instances->x -= 5;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		if (control_map_limits(infor, infor->p_img->instances->x + 5 + (infor->tile.base / 2), infor->p_img->instances->y) == 1)
			infor->p_img->instances->x += 5;
	}
}