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
	int	i;

	chars = "01NSEW ";
	i = 0;
	while (line[i])
	{
		if (!ft_strchr(chars, line[i]) && line[i] != '\n')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

void	parse_map(t_game *game, char *line, int fd)
{
	int	i;
	char	*buffer;

	i = 0;
	buffer = ft_strdup("");
	while (line)
	{
		buffer = ft_strjoin(buffer, line);
		i++;
		line = ft_get_next_line(fd);
	}
	game->map->content = ft_split(buffer, '\n');
	return ;
}

int	parse(t_game *game, char *path)
{
	int	fd;
	char	*line;

	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd <= 0)
		return (print_error(FILE_OPEN));
	line = ft_get_next_line(fd);
	while(line)
	{
		if (!ft_strncmp(line, "\n", 2))
			;
		else if (!check_elem(line))
			parse_elem(game, line);
		else if (check_map(line))
			parse_map(game, line, fd);
		else if (!line)
			return (print_error(ERR));
		free(line);
		line = ft_get_next_line(fd);
	}
	(free(line), close(fd));
	return (EXIT_SUCCESS);
}
