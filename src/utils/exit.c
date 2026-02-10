/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:43:06 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/10 14:43:08 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_content(char **content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		free(content[i]);
		i++;
	}
	free(content);
}

int key_hook(int keycode, t_game *game)
{
    if (keycode == ESC_KEY)
        exit_game(game);
    return (0);
}

int	exit_game(t_game *game)
{
	if (!game)
		exit(0);
	if (game->map)
	{
		if (game->asset->NO)
			mlx_destroy_image(game->mlx, game->asset->NO);
		if (game->asset->SO)
			mlx_destroy_image(game->mlx, game->asset->SO);
		if (game->asset->EA)
			mlx_destroy_image(game->mlx, game->asset->EA);
		if (game->asset->WE)
			mlx_destroy_image(game->mlx, game->asset->WE);
		free_content(game->map);
	}
	if (game->img && game->img->img)
		mlx_destroy_image(game->mlx, game->img->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	free(game->asset);
	free(game->player);
	free(game->img);
	free(game);
	exit(EXIT_SUCCESS);
	return (0);
}

