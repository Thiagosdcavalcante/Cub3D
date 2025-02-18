/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:54:52 by tsantana          #+#    #+#             */
/*   Updated: 2025/02/18 19:53:13 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	find_player(char c)
{
	return(c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

void	start_cam_infor(t_game *game)
{
	t_map	*map;
	
	map = game->map_position;
	while (find_player(map->content))
		map = map->nxt;
	game->cam->plr_x = (map->column * game->tile.base) + game->tile.base / 2;
	game->cam->plr_y = (map->line * game->tile.base) + game->tile.base / 2;
	game->cam->fov_plr = (FOV * M_PI) / 180;
	if (map->content == 'N')
		game->cam->angle = M_PI * NORTH;
	else if (map->content == 'S')
		game->cam->angle = M_PI * SOUTH;
	else if (map->content == 'W')
		game->cam->angle = M_PI * WEST;
	else if (map->content == 'E')
		game->cam->angle = M_PI * EAST;
	printf("plr_x: %f plr_y: %f dir: %c angle: %f\n", game->player.pos_x, game->player.pos_y, game->player.dir, game->cam->angle);
}