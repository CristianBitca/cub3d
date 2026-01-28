/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:43:06 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/10 14:43:08 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_content(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->content[i]);
	}
	free(map->content);
}

void	parse_error(t_game *game, char *line, int fd)
{
	if (!line)
		free(line);
	if (!fd)
		close(fd);
	if (!game->map)
	{
		if (!game->map->NO)
			mlx_destroy_image(game->mlx, game->map->NO);
		if (!game->map->SO)
			mlx_destroy_image(game->mlx, game->map->SO);
		if (!game->map->EA)
			mlx_destroy_image(game->mlx, game->map->EA);
		if (!game->map->WE)
			mlx_destroy_image(game->mlx, game->map->WE);
		if (!game->map->content)
			free_content(game->map);
	}
	free(game->map);
	if (!game->mlx)
		free(game->mlx);
}

void	error(void)
{
	static int	status;

	if (!status)
	{
		printf(ERR);
		status = 1;
	}
}

int	exit_error(char *err)
{
	error();
	printf("%s", err);
	exit(EXIT_FAILURE);
}
