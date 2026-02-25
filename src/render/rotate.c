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
