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

int	check_map(char *line)
{
	char	*chars;
	char	*count;
	int		i;
	int		c;

	chars = "01NSEW ";
	count = "NSEW";
	i = 0;
	c = 0;
	while (line[i])
	{
		if (!ft_strchr(chars, line[i]) && line[i] != '\n')
			exit_error(MAP_CHAR);
		if (ft_strchr(count, line[i]) && line[i] != '\n')
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
	game->map->content = ft_split(buffer, '\n');
	return ;
}

int	parse(t_game *game, char *path)
{
	int		fd;
	char	*line;

	line = NULL;
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
		else if (!line)
			return (exit_error(ERR));
		free(line);
		line = ft_get_next_line(fd);
	}
	(free(line), close(fd));
	return (EXIT_SUCCESS);
}
