/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:04:33 by tsantana          #+#    #+#             */
/*   Updated: 2024/10/28 21:32:33 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"

# define WIDTH 1920
# define HEIGHT 1050

typedef struct s_tile
{
	int	base;
	int	tile;
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
	t_map	*n;
	t_map	*s;
	t_map	*e;
	t_map	*player;
}	t_cam;

#endif
