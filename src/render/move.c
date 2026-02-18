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

void	calc_move(t_game *game, double *new_x, double *new_y, t_key_code key)
{
	double	move_step;

	move_step = game->move_speed * delta_time(game);
	if (key == W_KEY)
	{
		*new_x = game->player->x + game->player->dir_x * move_step;
		*new_y = game->player->y + game->player->dir_y * move_step;
	}
	else if (key == S_KEY)
	{
		*new_x = game->player->x - game->player->dir_x * move_step;
		*new_y = game->player->y - game->player->dir_y * move_step;
	}
	else if (key == D_KEY)
	{
		*new_x = game->player->x - game->player->dir_y * move_step;
		*new_y = game->player->y + game->player->dir_x * move_step;
	}
	else if (key == A_KEY)
	{
		*new_x = game->player->x + game->player->dir_y * move_step;
		*new_y = game->player->y - game->player->dir_x * move_step;
	}
}

void	move(t_game *game, t_key_code key)
{
	double	new_x;
	double	new_y;

	calc_move(game, &new_x, &new_y, key);
	if (game->map[(int)new_y][(int)game->player->x] != '1')
		game->player->y = new_y;
	if (game->map[(int)game->player->y][(int)new_x] != '1')
		game->player->x = new_x;
}

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
