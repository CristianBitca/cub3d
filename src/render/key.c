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

// FUNCTION: key_press
// ----------------------------
// Handles key press events. Sets the corresponding key flags in the game structure
// or triggers actions like exiting the game or toggling debug mode.
//
// PARAMETERS
// keycode : The keycode of the key that was pressed.
// game    : Pointer to the game structure containing the current key state and debug mode.
//
// RETURN VALUE
// Returns 0.
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


// FUNCTION: key_release
// ----------------------------
// Handles key release events. Clears the corresponding key flags in the game structure.
//
// PARAMETERS
// keycode : The keycode of the key that was released.
// game    : Pointer to the game structure containing the current key state.
//
// RETURN VALUE
// Returns 0.
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

// FUNCTION: handle_move
// ----------------------------
// Processes player movement and rotation based on the current state of the key flags.
// Moves the player forward, backward, strafing left/right, or rotates the view.
//
// PARAMETERS
// game : Pointer to the game structure containing the key states and player information.
//
// RETURN VALUE
// None.
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
