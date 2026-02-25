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

void	move(t_game *game, t_key_code key)
{
	double	move_x;
	double	move_y;

	calc_move(game, &move_x, &move_y, key);
	move_with_collision(game, move_x, move_y);
}
