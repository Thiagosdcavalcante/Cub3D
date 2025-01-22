/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 23:53:21 by leobarbo          #+#    #+#             */
/*   Updated: 2025/01/20 19:06:58 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	data;

	if(argc != 2)
		return (err_msg("Invalid number of arguments!", 1));
	init_data(&data);
	if (parsing(&data, argv) == ERROR)
		clean_exit(&data, 1);
	data.mlx_on = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	init_background(&data);
	mlx_loop(data.mlx_on);
	mlx_terminate(data.mlx_on);
	return (0);
}
