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
			free(line);
		else if (!check_elem(line))
			parse_elem(game, line);
		else if (!check_map(line))
			parse_map(game, line, fd);
		else if (line)
			return (exit_error(ERR));
		line = ft_get_next_line(fd);
	}
	(free(line), close(fd));
	// if (check_assets(game->asset))
	// 	exit_error(NULL);
	return (EXIT_SUCCESS);
}
