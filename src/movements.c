/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:25:20 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/22 17:46:30 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void ft_reles(mlx_key_data_t keydata, t_game *gm) // release the key
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		gm->cam->l_r = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		gm->cam->l_r = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		gm->cam->rotation = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		gm->cam->rotation = 0;
}

void    mlx_key(mlx_key_data_t keydata, void *ml) // key press
{
	t_game *gm;

	gm = (t_game *)ml;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) // exit the game
    {
        mlx_close_window(gm->mlx_on);
		// ft_exit(gm);
    }
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS)) // move left
		gm->cam->l_r = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS)) // move right
		gm->cam->l_r = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS)) // move down
		gm->cam->l_r = -1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) // rotate left
		gm->cam->rotation = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // rotate right
		gm->cam->rotation = 1;
	ft_reles(keydata, gm); // release the key
}

void rotate_player(t_game *gm, int i) // rotate the player
{
	if (i == 1)
	{
		gm->cam->angle += ROT_SPEED; // rotate right
		if (gm->cam->angle > 2 * M_PI)
			gm->cam->angle -= 2 * M_PI;
	}
	else
	{
		gm->cam->angle -= ROT_SPEED; // rotate left
		if (gm->cam->angle < 0)
			gm->cam->angle += 2 * M_PI;
	}
}

void move_player(t_game *gm, double move_x, double move_y) // move the player
{
	int     map_grid_y;
	int     map_grid_x;
	int     new_x;
	int     new_y;
    t_map   *map;

    map = gm->map;
	new_x = roundf(gm->cam->plr_x + move_x); // get the new x position
	new_y = roundf(gm->cam->plr_y + move_y); // get the new y position
	map_grid_x = (new_x / gm->tile.base); // get the x position in the map
	map_grid_y = (new_y / gm->tile.base); // get the y position in the map
	while (map)
    {
        if (map->column == map_grid_y && map->line == map_grid_x)
            break ;
        map = map->nxt;
    }
    if (map && map->content == '0')
	{
		gm->cam->plr_x = new_x; // move the player
		gm->cam->plr_y = new_y; // move the player
	}
}

void hook(t_game *gm, double move_x, double move_y) // hook the player
{
	if (gm->cam->rotation == 1) //rotate right
		rotate_player(gm, 1);
	if (gm->cam->rotation == -1) //rotate left
		rotate_player(gm, 0);
	if (gm->cam->l_r == 1) //move right
	{
		move_x = -sin(gm->cam->angle);
		move_y = cos(gm->cam->angle);
	}
	if (gm->cam->l_r == -1) //move left
	{
		move_x = sin(gm->cam->angle);
		move_y = -cos(gm->cam->angle);
	}
	move_player(gm, move_x, move_y); // move the player
}