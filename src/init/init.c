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
	img->img = mlx_new_image(game->mlx, 1920, 1080);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
}

void	init_player(t_player *player)
{
	player->y += 0.5;
	player->x += 0.5;
	if (player->orientation == 'N')
		(player->dir_x = 0, player->dir_y = -1);
	if (player->orientation == 'S')
		(player->dir_x = 0, player->dir_y = 1);
	if (player->orientation == 'E')
		(player->dir_x = 1, player->dir_y = 0);
	if (player->orientation == 'W')
		(player->dir_x = -1, player->dir_y = 0);
	player->plane_y = player->dir_x * 0.66;
	player->plane_x = -player->dir_y * 0.66;
}

void	init_data(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_error(MLX_MLX);
	game->win = mlx_new_window(game->mlx, 1920, 1080, "cub3D");
	if (!game->win)
		exit_error(MLX_WIN);
	game->asset = ft_calloc(sizeof(t_asset), 1);
	if (!game->asset)
		exit_error(ASSET_MEM);
	game->player = ft_calloc(sizeof(t_player), 1);
	if (!game->player)
		exit_error(PLAYER_MEM);
	game->img = ft_calloc(sizeof(t_img), 1);
	if (!game->img)
		exit_error(IMG_MEM);
	mlx_get_screen_size(game->mlx, &game->screen_width, &game->screen_height);
}

void	init_game(t_game *game, char *path)
{
	game->debug_mode = 0;
	init_data(game);
	parse(game, path);
	init_player(game->player);
	init_img(game, game->img);
	mlx_hook(game->win, CLOSE_ICON, 0, &exit_game, game);
	mlx_key_hook(game->win, &key_hook, game);
	if (game->debug_mode)
	{
		data_preview(game);
	}
	else
	{
		mlx_loop_hook(game->mlx, &render, game);
		mlx_loop(game->mlx);
	}
}
