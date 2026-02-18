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

void	free_img(t_game *game, t_img **img)
{
	if ((*img)->img)
		mlx_destroy_image(game->mlx, (*img)->img);
	(void)game;
}

int	exit_game(t_game *game)
{
	if (!game)
		exit(0);
	if (game->map)
		free_content(game->map);
	if (game->img && game->img->img)
		mlx_destroy_image(game->mlx, game->img->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	free_img(game, &game->asset->EA);
	free(game->asset->EA);
	free_img(game, &game->asset->WE);
	free(game->asset->WE);
	free_img(game, &game->asset->SO);
	free(game->asset->SO);
	free_img(game, &game->asset->NO);
	free(game->asset->NO);
	free(game->asset);
	free(game->player);
	free(game->img);
	free(game->key);
	free(game);
	exit(EXIT_SUCCESS);
	return (0);
}
