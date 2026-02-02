/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:40:02 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/10 17:40:03 by cbitca           ###   ########.fr       */
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

int	check_map_valid(char *content, t_map *map)
{
	char	**buffer;

	buffer = ft_split(content, '\n');
	while(buffer[map->y])
	{
		map->x = 0;
		while(buffer[map->y][map->x])
		{
			if (ft_strchr(ENTRY_CHARS, buffer[map->y][map->x])
			&& buffer[map->y][map->x] != '\n')
			{
				flood_fill(buffer, map->y, map->x);
				free_content(buffer);
				return (EXIT_SUCCESS);
			}
			map->x++;
		}
		map->y++;
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

	game->map->height = 0;
	game->map->width = ft_strlen(line);
	buffer = ft_strdup("");
	while (line)
	{
		tmp = buffer;
		buffer = ft_strjoin(buffer, line);
		(free(tmp), free(line));
		line = ft_get_next_line(fd);
		game->map->height++;
		if (ft_strlen(line) > (size_t)game->map->width)
			game->map->width = ft_strlen(line);
	}
	if (check_map(buffer))
		exit_error(NULL);
	if (check_map_valid(buffer, game->map))
		exit_error(NULL);
	game->map->content = ft_split(buffer, '\n');
	free(buffer);
}

int	parse(t_game *game, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
		exit_error(FILE_OPEN);
	line = ft_get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "\n", 2))
			;
		else if (!check_elem(line))
			parse_elem(game, line);
		else if (!check_map(line))
			parse_map(game, line, fd);
		else if (line)
			return (exit_error(ERR));;
		line = ft_get_next_line(fd);
	}
	(free(line), close(fd));
	if (check_assets(game->map))
		exit_error(NULL);
	return (EXIT_SUCCESS);
}
