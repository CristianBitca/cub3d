/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:54:07 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/25 13:54:09 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "parsing.h"

// FUNCTION: rotate_left
// ----------------------------
// Rotates the player's view to the left (counter-clockwise) by the rotation speed
// scaled with delta_time. Updates both the direction vector and the camera plane.
//
// PARAMETERS
// game : Pointer to the game structure containing the player direction, camera plane, 
//        and rotation speed.
//
// RETURN VALUE
// None. Updates the player's dir_x, dir_y, plane_x, and plane_y values in the game structure.
void	rotate_left(t_game *game)
{
	double	rot_step;
	double	old_dir_x;
	double	old_plane_x;

	rot_step = game->rot_speed * delta_time(game);
	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(rot_step)
		- game->player->dir_y * sin(rot_step);
	game->player->dir_y = old_dir_x * sin(rot_step)
		+ game->player->dir_y * cos(rot_step);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(rot_step)
		- game->player->plane_y * sin(rot_step);
	game->player->plane_y = old_plane_x * sin(rot_step)
		+ game->player->plane_y * cos(rot_step);
}

// FUNCTION: rotate_right
// ----------------------------
// Rotates the player's view to the right (clockwise) by the rotation speed
// scaled with delta_time. Updates both the direction vector and the camera plane.
//
// PARAMETERS
// game : Pointer to the game structure containing the player direction, camera plane, 
//        and rotation speed.
//
// RETURN VALUE
// None. Updates the player's dir_x, dir_y, plane_x, and plane_y values in the game structure.

void	rotate_right(t_game *game)
{
	double	rot_step;
	double	old_dir_x;
	double	old_plane_x;

	rot_step = -game->rot_speed * delta_time(game);
	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(rot_step)
		- game->player->dir_y * sin(rot_step);
	game->player->dir_y = old_dir_x * sin(rot_step)
		+ game->player->dir_y * cos(rot_step);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(rot_step)
		- game->player->plane_y * sin(rot_step);
	game->player->plane_y = old_plane_x * sin(rot_step)
		+ game->player->plane_y * cos(rot_step);
}
