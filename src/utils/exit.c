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

// FUNCTION: free_content
// ----------------------------
// Frees a null-terminated array of strings.
//
// PARAMETERS
// content : Pointer to a dynamically allocated array of strings.
//
// RETURN VALUE
// None.
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

// FUNCTION: free_img
// ----------------------------
// Frees an mlx image if it exists.
//
// PARAMETERS
// game : Pointer to the main game structure (used for mlx functions).
// img  : Pointer to the t_img pointer to free.
//
// RETURN VALUE
// None.
void	free_img(t_game *game, t_img **img)
{
	if ((*img)->img)
		mlx_destroy_image(game->mlx, (*img)->img);
	(void)game;
}

// FUNCTION: free_mlx
// ----------------------------
// Frees the mlx window and display resources.
//
// PARAMETERS
// game : Pointer to the main game structure.
//
// RETURN VALUE
// None.
void	free_mlx(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

// FUNCTION: exit_game
// ----------------------------
// Frees all allocated game resources and exits the program.
//
// PARAMETERS
// game : Pointer to the main game structure.
//
// RETURN VALUE
// Exits the program with EXIT_SUCCESS. Returns 0 for compatibility, but
// it never actually returns.
int	exit_game(t_game *game)
{
	if (!game)
		exit(0);
	if (game->map)
		free_content(game->map);
	if (game->img && game->img->img)
		mlx_destroy_image(game->mlx, game->img->img);
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
	free_mlx(game);
	free(game);
	exit(EXIT_SUCCESS);
	return (0);
}
