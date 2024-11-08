/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:26:50 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/08 18:59:24 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

void	control_hooks(mlx_key_data_t keydata, void *param)
{
	t_game	*infor;

	infor = (t_game *)param;
	if (keydata.key == MLX_KEY_UP)
		infor->p_img->instances->y -= 5;
	if (keydata.key == MLX_KEY_DOWN)
		infor->p_img->instances->y += 5;
	if (keydata.key == MLX_KEY_LEFT)
		infor->p_img->instances->x -= 5;
	if (keydata.key == MLX_KEY_RIGHT)
		infor->p_img->instances->x += 5;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(infor->mlx_on);
}