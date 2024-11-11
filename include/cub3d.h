/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:04:33 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/11 17:04:51 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# define WIDTH 1920
# define HEIGHT 1080
# define FOV 66
# define ROT_SPEED 0.040
# define MAX_MAP_W 640
# define MAX_MAP_H 360
# define CYAN 0x00FFFF

typedef struct s_tile
{
	int	base;
	int	width;
	int	height;
}	t_tile;

typedef struct s_image
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;
}	t_img;

typedef struct s_render_img
{
	int	x;
	int	y;
	int	z;
}	t_r_img;

typedef struct s_object
{
	int		onoff;
	t_img	img;
	t_r_img	sizes;
}	t_obj;

typedef struct s_map
{
	int				line;
	int				column;
	char			content;
	struct s_map	*nxt;
	struct s_map	*prv;
}	t_map;

typedef struct s_cam
{
	int		plr_x;
	int		plr_y;
	int		rotation;
	double	angler;
	float	fov;
}	t_cam;

typedef struct s_game
{
	mlx_image_t	*img;
	mlx_image_t	*p_img;
	t_tile		tile;
	mlx_t		*mlx_on;
	t_map		*map;
	t_cam		*cam;
}	t_game;

void	render_elements(mlx_t *win, t_map *map, t_game *gm);
void	control_hooks(mlx_key_data_t keydata, void *param);
void	free_all(t_game *gm);
void	init_minimap(t_game *gm);

#endif
