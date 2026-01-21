/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:39:42 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/10 17:39:43 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

int	ft_render(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < 300)
	{
		y = 0;
		while (y < 300)
		{
			mlx_pixel_put(game->mlx, game->win, x, y, game->map->C);
			y++;
		}
		x++;
	}
	return (EXIT_SUCCESS);
}

int	init_game(t_game *game, char *path)
{
	game->mlx = mlx_init();
	game->map = ft_calloc(sizeof(t_map), 1);
	parse(game, path);
	game->win = mlx_new_window(game->mlx, 1920, 1080, "cub3D");
	mlx_loop_hook(game->mlx, &ft_render, game);
	mlx_loop(game->mlx);
	free(game->mlx);
	return (EXIT_SUCCESS);
}
