/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:37:35 by tsantana          #+#    #+#             */
/*   Updated: 2025/02/08 14:29:48 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// static mlx_texture_t	*construct_texture(t_game *gm, char *png)
// {
// 	mlx_texture_t	*tmp;
// 	int32_t			fd;
// 	int32_t			len;

// 	len = ft_strlen(png);
// 	if (len < 4 && ft_strncmp(&png[len - 4], ".png", 5) != 0)
// 		return (ft_printf("Invalid .png texture"), NULL);
// 	fd = open(png, O_RDONLY, 0644);
// 	if (fd < 1)
// 		return (ft_printf("Impossible to load texture"), NULL);
// 	close(fd);
// 	tmp = mlx_load_png(png);
// 	if (!tmp)
// 		return(ft_printf("Failed to load texture"), NULL);
// 	return (tmp);
// }

// // t_texture	*init_texture(t_texinfo *infor)
// // {
// //     t_texture	*texture;
    
// //     texture = (t_texture *)malloc(sizeof(t_texture));
    
// //     return (texture);
// // }