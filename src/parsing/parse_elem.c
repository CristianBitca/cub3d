/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:06:20 by cbitca            #+#    #+#             */
/*   Updated: 2026/01/18 16:06:21 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "utils.h"

void	parse_rgb(int *p_elem, char **elem)
{
	char	**tmp;
	int	r;
	int	g;
	int	b;

	tmp = &elem[1];
	elem[1] = ft_strtrim(elem[1], "\n\t");
	tmp = ft_split(elem[1], ',');
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	*p_elem = (r << 16) | (g << 8) | b;
}

void	parse_img(void *mlx, void **p_elem, char **elem)
{
	int	width;
	int	height;
	char	*tmp;

	width = 0;
	height = 0;
	tmp = ft_strtrim(elem[1], "\n\t");
	if (ft_atoi(&tmp[0]) && ft_atoi(&tmp[1]) && ft_atoi(&tmp[2]))
		printf("Erros\n");
	*p_elem = mlx_xpm_file_to_image(mlx, tmp, &width, &height);
	if (!*p_elem)
		printf(XPM_FILE, tmp, elem[0]);
	free(tmp);
}

void	parse_elem(t_game *game, char *line)
{
	char	**element;

	element = ft_split(line, ' ');
	if (!ft_strncmp("NO", element[0], 3))
		parse_img(game->mlx, &game->map->NO, element);
	else if (!ft_strncmp("SO", element[0], 3))
		parse_img(game->mlx, &game->map->SO, element);
	else if (!ft_strncmp("WE", element[0], 3))
		parse_img(game->mlx, &game->map->WE, element);
	else if (!ft_strncmp("EA", element[0], 3))
		parse_img(game->mlx, &game->map->EA, element);
	else if (!ft_strncmp("F", element[0], 2))
		parse_rgb(&game->map->F, element);
	else if (!ft_strncmp("C", element[0], 2))
		parse_rgb(&game->map->C, element);
	(free(element[0]), free(element[1]), free(element));
}

int	check_elem(char	*line)
{
	char	**element;

	if (!ft_strchr(line, ' '))
		return (EXIT_FAILURE);
	if (count_words(line, ' ') != 2)
		return (EXIT_FAILURE);
	element = ft_split(line, ' ');
	if (ft_strlen(element[0]) > 2)
		return (EXIT_FAILURE);
	(free(element[0]), free(element[1]), free(element));
	return (EXIT_SUCCESS);
}

