/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:04:33 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/22 17:34:46 by tsantana         ###   ########.fr       */
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
# define MAX_MAP_W 480
# define MAX_MAP_H 270
# define CYAN 0x00FFFF

typedef struct	s_ray
{
 double	ray_ngl;
 double	distance;
 int	flag;
}				t_ray;

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
	int		l_r;
	double	angle;
	float	fov_plr;
}	t_cam;

typedef struct s_game
{
	int			is_horizon;
	mlx_image_t	*img;
	mlx_image_t	*game;
	mlx_image_t	*p_img;
	mlx_image_t	*bg_img;
	t_tile		tile;
	mlx_t		*mlx_on;
	t_map		*map;
	t_cam		*cam;
	t_ray		ray;
}	t_game;

// void	render_elements(mlx_t *win, t_map *map, t_game *gm);
void	control_hooks(mlx_key_data_t keydata, void *param);
void	free_all(t_game *gm);
void	init_minimap(t_game *gm);
void    init_background(t_game *gm);
int		control_map_limits(t_game *gm, int x, int y);

///////////////////////////////////////////////////////////////
///				RAYCASTING AND RENDER						///
///////////////////////////////////////////////////////////////

void	cast_rays(t_game *gm);
void	render_wall(t_game *gm, int ray);
void	draw_wall(t_game *gm, int ray, int t_pix, int b_pix);
void	my_mlx_pixel_put(t_game *gm, int x, int y, int color);
float	nor_angle(float angle);
float	get_v_inter(t_game *gm, float angl);
float	get_h_inter(t_game *gm, float angl);
int		get_color(t_game *gm, int flag);
int		unit_circle(float angle, char c);
int		wall_hit(float x, float y, t_game *gm);
int		inter_check(float angle, float *inter, float *step, t_game *gm);

///////////////////////////////////////////////////////////////
///				MOVEMENTS AND ROTATIONS						///
///////////////////////////////////////////////////////////////

void	hook(t_game *gm, double move_x, double move_y);
void	move_player(t_game *gm, double move_x, double move_y);
void	rotate_player(t_game *gm, int i);
void	mlx_key(mlx_key_data_t keydata, void *ml);
void	ft_reles(mlx_key_data_t keydata, t_game *gm);

#endif
