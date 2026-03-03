/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:54:14 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/14 16:54:16 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "parsing.h"

// FUNCTION: check_collision
// ----------------------------
// Checks whether the specified position (x, y) collides with walls on the map,
// including a small buffer to prevent clipping through corners.
//
// PARAMETERS
// game : Pointer to the game structure containing the map layout.
// x    : X-coordinate to check for collision.
// y    : Y-coordinate to check for collision.
//
// RETURN VALUE
// Returns 1 if a collision is detected, 0 otherwise.
int	check_collision(t_game *game, double x, double y)
{
	if (game->map[(int)y][(int)x] == '1')
		return (1);
	if (game->map[(int)(y - COLLISION_BUF)][(int)(x - COLLISION_BUF)] == '1')
		return (1);
	if (game->map[(int)(y - COLLISION_BUF)][(int)(x + COLLISION_BUF)] == '1')
		return (1);
	if (game->map[(int)(y + COLLISION_BUF)][(int)(x - COLLISION_BUF)] == '1')
		return (1);
	if (game->map[(int)(y + COLLISION_BUF)][(int)(x + COLLISION_BUF)] == '1')
		return (1);
	return (0);
}

// FUNCTION: move_with_collision
// ----------------------------
// Moves the player by the specified deltas while preventing movement through walls.
// Attempts full movement first, then separate X or Y movement if full move is blocked.
//
// PARAMETERS
// game   : Pointer to the game structure containing player and map data.
// move_x : Movement delta along the X-axis.
// move_y : Movement delta along the Y-axis.
//
// RETURN VALUE
// None. Updates the player position in the game structure.
void	move_with_collision(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player->x + move_x;
	new_y = game->player->y + move_y;
	if (!check_collision(game, new_x, new_y))
	{
		game->player->x = new_x;
		game->player->y = new_y;
		return ;
	}
	if (!check_collision(game, new_x, game->player->y))
	{
		game->player->x = new_x;
		return ;
	}
	if (!check_collision(game, game->player->x, new_y))
	{
		game->player->y = new_y;
		return ;
	}
}

// FUNCTION: calc_move
// ----------------------------
// Calculates the movement delta (new_x, new_y) based on the key pressed and
// the player's direction. Movement is scaled by move_speed and delta_time.
//
// PARAMETERS
// game  : Pointer to the game structure containing player direction and speed.
// new_x : Pointer to a double where the calculated X delta will be stored.
// new_y : Pointer to a double where the calculated Y delta will be stored.
// key   : Key pressed (W, A, S, D) indicating movement direction.
//
// RETURN VALUE
// None. Updates the values pointed to by new_x and new_y.
void	calc_move(t_game *game, double *new_x, double *new_y, t_key_code key)
{
	double	move_step;

	move_step = game->move_speed * delta_time(game);
	if (key == W_KEY)
	{
		*new_x = game->player->dir_x * move_step;
		*new_y = game->player->dir_y * move_step;
	}
	else if (key == S_KEY)
	{
		*new_x = -game->player->dir_x * move_step;
		*new_y = -game->player->dir_y * move_step;
	}
	else if (key == D_KEY)
	{
		*new_x = -game->player->dir_y * move_step;
		*new_y = game->player->dir_x * move_step;
	}
	else if (key == A_KEY)
	{
		*new_x = game->player->dir_y * move_step;
		*new_y = -game->player->dir_x * move_step;
	}
}

// FUNCTION: move
// ----------------------------
// Moves the player based on the key pressed, calculating movement delta and
// applying collision detection to prevent walking through walls.
//
// PARAMETERS
// game : Pointer to the game structure containing player, map, and movement data.
// key  : Key pressed (W, A, S, D) indicating movement direction.
//
// RETURN VALUE
// None. Updates the player position in the game structure.
void	move(t_game *game, t_key_code key)
{
	double	move_x;
	double	move_y;

	calc_move(game, &move_x, &move_y, key);
	move_with_collision(game, move_x, move_y);
}
