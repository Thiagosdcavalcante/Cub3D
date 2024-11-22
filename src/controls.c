/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:26:50 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/22 16:39:34 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

// int	check_down_limits(t_game *gm, int x, int y)
// {
// 	t_map	*map;
	
// 	map = gm->map;
// 		while (map && (map->line * gm->tile.base) <= y && (map->column * gm->tile.base) <= x)
// 		map = map->nxt;
// 	while (map && (map->line * gm->tile.base) > y && (map->column * gm->tile.base) > x)
// 		map = map->prv;
// 	if (map->content == '1')
// 		return (0);
// 	return (1);
// }

// void	control_hooks(mlx_key_data_t keydata, void *param)
// {
// 	t_game	*infor;
// 	int		len_step = 5;
	
// 	infor = (t_game *)param;
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
// 		mlx_close_window(infor->mlx_on);
// 	else if (keydata.key == MLX_KEY_W)
// 	{
// 		if (control_map_limits(infor, infor->p_img->instances->x, infor->p_img->instances->y - len_step) == 1)
// 			infor->p_img->instances->y -= len_step;
// 	}
// 	else if (keydata.key == MLX_KEY_S)
// 	{
// 		if (control_map_limits(infor, infor->p_img->instances->x, infor->p_img->instances->y + len_step) == 1)
// 			infor->p_img->instances->y += len_step;
// 	}
// 	else if (keydata.key == MLX_KEY_A)
// 	{
// 		if (control_map_limits(infor, infor->p_img->instances->x - len_step, infor->p_img->instances->y) == 1)
// 			infor->p_img->instances->x -= len_step;
// 	}
// 	else if (keydata.key == MLX_KEY_D)
// 	{
// 		if (control_map_limits(infor, infor->p_img->instances->x + len_step, infor->p_img->instances->y) == 1)
// 			infor->p_img->instances->x += len_step;
// 	}
// }