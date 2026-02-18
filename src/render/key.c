/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:55:23 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/14 16:55:25 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "parsing.h"
#include "utils.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		exit_game(game);
	if (keycode == M_KEY)
		game->debug_mode = !game->debug_mode;
	if (keycode == W_KEY)
		game->key->w = 1;
	if (keycode == A_KEY)
		game->key->a = 1;
	if (keycode == S_KEY)
		game->key->s = 1;
	if (keycode == D_KEY)
		game->key->d = 1;
	if (keycode == LEFT_ARROW_KEY)
		game->key->left = 1;
	if (keycode == RIGHT_ARROW_KEY)
		game->key->right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->key->w = 0;
	if (keycode == A_KEY)
		game->key->a = 0;
	if (keycode == S_KEY)
		game->key->s = 0;
	if (keycode == D_KEY)
		game->key->d = 0;
	if (keycode == LEFT_ARROW_KEY)
		game->key->left = 0;
	if (keycode == RIGHT_ARROW_KEY)
		game->key->right = 0;
	return (0);
}

void	handle_move(t_game *game)
{
	if (game->key->w)
		move(game, W_KEY);
	if (game->key->s)
		move(game, S_KEY);
	if (game->key->a)
		move(game, A_KEY);
	if (game->key->d)
		move(game, D_KEY);
	if (game->key->right)
		rotate_left(game);
	if (game->key->left)
		rotate_right(game);
}
