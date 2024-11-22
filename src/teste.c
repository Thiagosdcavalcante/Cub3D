
#include "../include/cub3d.h"

t_map	*new_node(int ln, int clmn, char cntnt)
{
	t_map	*node;

	node = malloc(sizeof(t_map));
	node->column = clmn;
	node->content = cntnt;
	node->line = ln;
	node->nxt = NULL;
	node->prv = NULL;
	return (node);
}

t_map	*parse_map(char *map, t_tile *tile)
{
	int		line = 0;
	int		column = 0;
	int		i = 0;
	t_map	*list;
	t_map	*head;

	list = NULL;
	tile->base = 0;
	tile->height = 0;
	tile->width = 0;
	while (map[i] != '\0')
	{
		column = 0;
		while (map[i] != '\0' && map[i] != '\n')
		{
			if (!list)
			{
				list = new_node(line, column, map[i]);
				head = list;
			}
			else
			{
				list->nxt = new_node(line, column, map[i]);
				list->nxt->prv = list;
				list = list->nxt;
			}
			column++;
			i++;
		}
		if (map[i])
		{
			line++;
			if (line > tile->width)
				tile->width = column;
			i++;
		}
	}
	tile->height = line + 1;
	if ((MAX_MAP_H / tile->height) > (MAX_MAP_W / tile->width))
		tile->base = (MAX_MAP_W / tile->width);
	else
		tile->base = (MAX_MAP_H / tile->height);
	return (head);
}

static float	angler_def(char direction)
{
    if (direction == 'N')
        return (-(3 * M_PI / 2));
    else if (direction == 'S')
        return (3 * M_PI / 2);
    else if (direction == 'W')
        return (M_PI);
    else
        return (0);
}

int	is_player(char content)
{
	return (content == 'N' || content == 'S' || content == 'W' || content == 'E');
}

t_cam	*find_player(t_game *gm)
{
	t_cam	*player;
	t_map	*ref;

	player = malloc(sizeof(t_cam));
	ref = gm->map;
	player->rotation = 0;
	player->l_r = 0;
	while (ref)
	{
		if (is_player(ref->content))
		{
			player->angle = angler_def(ref->content);
			player->plr_y = (ref->line * gm->tile.base) + (gm->tile.base / 4);
			player->plr_x = (ref->column * gm->tile.base) + (gm->tile.base / 4);
			break ;
		}
		ref = ref->nxt;
	}
	player->fov_plr = (float)((FOV * M_PI) / 180);
	ref->content = '0';
	return (player);
}

int	can_move(char direction)
{
	if (direction != '1')
		return (0);
	return (1);
}

void	game_loop(void *game)	// game loop
{
	t_game	*gm;

	gm = (t_game *)game;
	if (gm->game)	// cast to the mlx structure
		mlx_delete_image(gm->mlx_on, gm->game);	// delete the image
	gm->game = mlx_new_image(gm->mlx_on, WIDTH, HEIGHT);	// create new image
	hook(gm, 0, 0); // hook the player
	cast_rays(gm);	// cast the rays
	mlx_image_to_window(gm->mlx_on, gm->game, 0, 0); // put the image to the window
}

int	main(void)
{
	char	*map = "1111111111\n1000000001\n100000E001\n1000000001\n1111111111\0";
	t_game	gnrl;

	gnrl = (t_game){0};
	gnrl.ray = (t_ray){0};
	gnrl.map = parse_map(map, &gnrl.tile);
	gnrl.cam = find_player(&gnrl);
	gnrl.mlx_on = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	init_background(&gnrl);
	mlx_loop_hook(gnrl.mlx_on, &game_loop, &gnrl);
	// init_minimap(&gnrl);
	mlx_key_hook(gnrl.mlx_on, &mlx_key, &gnrl);
	mlx_loop(gnrl.mlx_on);
	mlx_terminate(gnrl.mlx_on);
	free_all(&gnrl);
	return (0);
}
