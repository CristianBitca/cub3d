/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:59:34 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/04 15:59:35 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "utils.h"

void	flood_fill(char **buffer, int y, int x)
{
	if (x < 0 || y < 0 || !buffer[y] || !buffer[y][x])
		exit_error(NULL);
	if (buffer[y][x] == ' ' || buffer[y][x] == '\0')
		exit_error(NULL);
	if (buffer[y][x] == '1' || buffer[y][x] == 'V')
		return ;
	buffer[y][x] = 'V';
	flood_fill(buffer, y + 1, x);
	flood_fill(buffer, y - 1, x);
	flood_fill(buffer, y, x + 1);
	flood_fill(buffer, y, x - 1);
}

int	check_map_valid(char *content, t_player *player)
{
	char	**buffer;
	int		y;
	int		x;

	buffer = ft_split(content, '\n');
	y = 0;
	while(buffer[y])
	{
		x = 0;
		while(buffer[y][x])
		{
			if (ft_strchr(ENTRY_CHARS, buffer[y][x])
			&& buffer[y][x] != '\n')
			{
				flood_fill(buffer, y, x);
				player->y = (double)y;
				player->x = (double)x;
				player->orientation = buffer[y][x];
				return (free_content(buffer), EXIT_SUCCESS);
			}
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

int	check_map(char *line)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (line[i])
	{
		if (!ft_strchr(MAP_CHARS, line[i]) && line[i] != '\n')
			exit_error(MAP_CHAR);
		if (ft_strchr(ENTRY_CHARS, line[i]) && line[i] != '\n')
			c++;
		i++;
	}
	if (c != 0 && c != 1)
		exit_error(MAP_ENTRY);
	return (EXIT_SUCCESS);
}

void	parse_map(t_game *game, char *line, int fd)
{
	char	*buffer;
	char	*tmp;

	buffer = ft_strdup("");
	while (line)
	{
		tmp = buffer;
		buffer = ft_strjoin(buffer, line);
		(free(tmp), free(line));
		line = ft_get_next_line(fd);
	}
	if (check_map(buffer))
		exit_error(NULL);
	if (check_map_valid(buffer, game->player))
		exit_error(NULL);
	game->map = ft_split(buffer, '\n');
	free(buffer);
}