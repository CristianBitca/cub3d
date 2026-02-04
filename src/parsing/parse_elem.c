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

int	check_rgb(char	*line)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (EXIT_FAILURE);
		if (line[i] == ',')
			c++;
		i++;
	}
	if (c != 2)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	parse_rgb(int *p_elem, char **elem)
{
	char	**tmp;
	int		r;
	int		g;
	int		b;

	if (check_rgb(elem[1]))
	{
		(error(), printf(RGB, elem[0], elem[1]));
		return ;
	}
	tmp = ft_split(elem[1], ',');
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	if (!(0 <= r && 255 >= r)
		|| !(0 <= g && 255 >= g)
		|| !(0 <= b && 255 >= b))
	{
		(error(), printf(RGB, elem[0], elem[1]));
		(free(tmp[0]), free(tmp[1]), free(tmp[2]), free(tmp));
		return ;
	}
	*p_elem = (r << 16) | (g << 8) | b;
	(free(tmp[0]), free(tmp[1]), free(tmp[2]), free(tmp));
}

void	parse_img(void *mlx, void **p_elem, char **elem)
{
	int		width;
	int		height;
	char	*tmp;

	width = 0;
	height = 0;
	tmp = ft_strtrim(elem[1], "\n\t");
	if (ft_strncmp(&tmp[ft_strlen(tmp) - 4], IMG_FORMAT, 4))
		(error(), printf(IMG_EXT, elem[0]));
	*p_elem = mlx_xpm_file_to_image(mlx, tmp, &width, &height);
	if (!*p_elem)
		(error(), printf(XPM_FILE, tmp, elem[0]));
	free(tmp);
}

void	parse_elem(t_game *game, char *line)
{
	char	**element;
	char	*tmp;

	element = ft_split(line, ' ');
	tmp = element[1];
	element[1] = ft_strtrim(element[1], "\n\t");
	free(tmp);
	if (!ft_strncmp("NO", element[0], 3))
		parse_img(game->mlx, &game->asset->NO, element);
	else if (!ft_strncmp("SO", element[0], 3))
		parse_img(game->mlx, &game->asset->SO, element);
	else if (!ft_strncmp("WE", element[0], 3))
		parse_img(game->mlx, &game->asset->WE, element);
	else if (!ft_strncmp("EA", element[0], 3))
		parse_img(game->mlx, &game->asset->EA, element);
	else if (!ft_strncmp("F", element[0], 2))
		parse_rgb(&game->asset->F, element);
	else if (!ft_strncmp("C", element[0], 2))
		parse_rgb(&game->asset->C, element);
	else
		(error(), printf(EXTRA_ELEM, element[0], element[1]));
	(free_content(element), free(line));
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
	{
		(free(element[0]), free(element[1]), free(element));
		return (EXIT_FAILURE);
	}
	(free(element[0]), free(element[1]), free(element));
	return (EXIT_SUCCESS);
}
