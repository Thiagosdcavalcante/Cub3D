/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:34:39 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/07 15:04:45 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_map(t_map *map)
{
	t_map	*ref;

	while (map)
	{
		ref = map;
		map = map->nxt;
		ref->prv = NULL;
		ref->nxt = NULL;
		free(ref);
		ref = NULL;
	}
	if (map)
	{
		free(map);
		map = NULL;
	}
}

void	free_all(t_game *gm)
{
	if (gm->map)
		free_map(gm->map);
	if (gm->cam)
		free(gm->cam);
}
