/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 19:47:04 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/10 19:47:05 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h"

void	print_player(t_player *player)
{
	printf("X = %d Y = %d\n", (int)player->x, (int)player->y);
	printf("\t\tDir X = %f Y = %f\n", player->dir_x, player->dir_y);
	printf("\t\tPlane X = %f Y = %f\n", player->plane_x, player->plane_y);
	(void)player;
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	printf("\n");
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	printf("\n");
}

void	print_data_prev(void *mem, char *elem, t_data_type type)
{
	printf("%s", elem);
	if (type == INT)
		printf("%d\n", *(int *)mem);
	if (type == DOUBLE)
		printf("%f\n", *(double *)mem);
	else if (type == CHAR)
		print_map((char **)mem);
	else if (type == PLAYER)
		print_player((t_player*)mem);
	else if (type == ASSET)
		printf("asset exist\n");
	else if (type == VOID)
	{
		if (mem)
			printf("succes\n");
		else
			printf("fail\n");
	}
}

void	data_preview(t_game *game)
{
	print_data_prev(game->mlx, "MLX\t\t", VOID);
	print_data_prev(game->win, "WIN\t\t", VOID);
	print_data_prev(&game->screen_width, "Screen width\t", INT);
	print_data_prev(&game->screen_height, "Screen height\t", INT);
	print_data_prev(&game->map_width, "Map width\t", INT);
	print_data_prev(&game->map_height, "Map height\t", INT);
	print_data_prev(game->map, "Map overview\n", CHAR);
	print_data_prev(game->player, "Player info:\t", PLAYER);
	print_data_prev(game->asset, "Assets:\t", ASSET);
	print_data_prev(&game->move_speed, "Move speed\t", DOUBLE);
	print_data_prev(&game->rot_speed, "Rotation speed\t", DOUBLE);
}
