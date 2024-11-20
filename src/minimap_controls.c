/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_controls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:05:33 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/20 15:12:15 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int  limits_checker(t_map *origin, int x, int y)
{
    t_map	*map;
	
	map = origin;
	while (map)
	{
		if (map->line == y && map->column == x)
			break ;
		map = map->nxt;
	}
	if (map->content == '1')
		return (0);
    return (1);
}

int	control_map_limits(t_game *gm, int x, int y)
{
	t_map	*map;
	int		new_y;
	int		new_x;
	
	map = gm->map;
	new_x = (x + (gm->tile.base/2)) / gm->tile.base;
	new_y = (y + (gm->tile.base/2)) / gm->tile.base;
	x /= gm->tile.base;
	y /= gm->tile.base;
	if (limits_checker(gm->map, x, y) == 0)
		return (0);
    if (limits_checker(gm->map, new_x, y) == 0)
        return (0);
    if (limits_checker(gm->map, x, new_y) == 0)
        return (0);
    if (limits_checker(gm->map, new_x, new_y) == 0)
        return (0);
    return (1);
}