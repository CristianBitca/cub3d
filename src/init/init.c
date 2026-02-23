/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:39:42 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/10 17:39:43 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "render.h"
#include "utils.h"

void	init_img(t_game *game, t_img *img)
{
	game->win = mlx_new_window(game->mlx, game->screen_width,
			game->screen_height, "cub3D");
	if (!game->win)
		exit_error(MLX_WIN);
	img->img = mlx_new_image(game->mlx,
			game->screen_width, game->screen_height);
	img->addr = mlx_get_data_addr(img->img,
			&img->bpp, &img->line_len, &img->endian);
}

void	init_player(t_game *game, t_player *player)
{
	if (game->map[(int)player->y][(int)player->x] == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	if (game->map[(int)player->y][(int)player->x] == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	if (game->map[(int)player->y][(int)player->x] == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	if (game->map[(int)player->y][(int)player->x] == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	player->y += 0.5;
	player->x += 0.5;
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
}

void	init_data(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_error(MLX_MLX);
	mlx_get_screen_size(game->mlx, &game->screen_width, &game->screen_height);
	if (game->screen_width == 0 && game->screen_height == 0)
		exit_error(SCREEN_SIZE);
	game->asset = ft_calloc(sizeof(t_asset), 1);
	if (!game->asset)
		exit_error(ASSET_MEM);
	game->player = ft_calloc(sizeof(t_player), 1);
	if (!game->player)
		exit_error(PLAYER_MEM);
	game->key = ft_calloc(sizeof(t_key), 1);
	if (!game->key)
		exit_error(KEY_MEM);
	game->img = ft_calloc(sizeof(t_img), 1);
	if (!game->img)
		exit_error(IMG_MEM);
	game->move_speed = 1.0;
	game->rot_speed = 1.0;
}

void	init_game(t_game *game, char *path)
{
	init_data(game);
	parse(game, path);
	init_player(game, game->player);
	init_img(game, game->img);
	mlx_hook(game->win, CLOSE_ICON, 0, &exit_game, game);
	mlx_hook(game->win, KEY_PRESS, 1L << 0, &key_press, game);
	mlx_hook(game->win, KEY_RELEASE, 1L << 1, &key_release, game);
	mlx_loop_hook(game->mlx, &render, game);
	data_preview(game);
	game->debug_mode = 0;
	mlx_loop(game->mlx);
}
