/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:29:29 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/10 14:29:30 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

int	check_arg(int argc, char **argv)
{
	if (argc < 2)
		return (printf(ARG_1));
	if (argc > 2)
		return (printf(ARG_3));
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], MAP_FORMAT, 4))
		return (printf(ARG_2));
	return (EXIT_SUCCESS);
}

int	check_assets(t_asset *asset)
{
	if (!asset->EA)
		exit_error(NULL);
	if (!asset->NO)	
		exit_error(NULL);
	if (!asset->SO)
		exit_error(NULL);
	if (!asset->WE)
		exit_error(NULL);
	return (EXIT_SUCCESS);
}
