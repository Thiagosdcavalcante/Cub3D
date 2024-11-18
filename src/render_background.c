/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:24:18 by tsantana          #+#    #+#             */
/*   Updated: 2024/11/14 16:13:45 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    init_background(t_game *gm)
{
    int max_h;
    int i;
    int j;

    gm->bg_img = mlx_new_image(gm->mlx_on, WIDTH, HEIGHT);
    max_h = HEIGHT / 2;
    j = 0;
    while (j < HEIGHT)
    {
        i = 0;
        while (i < WIDTH)
        {
            if (j < max_h)
                mlx_put_pixel(gm->bg_img, i, j, 0xb9ebfaFF);
            else
                mlx_put_pixel(gm->bg_img, i, j, 0x707070FF);
            i++;
        }
        j++;
    }
    mlx_image_to_window(gm->mlx_on, gm->bg_img, 0, 0);
}