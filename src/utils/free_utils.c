/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:29:21 by mtice             #+#    #+#             */
/*   Updated: 2025/12/08 15:40:17 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//frees a 2d array
static void	free_double_char(char **arr)
{
	int	j;

	j = 0;
	while (arr[j] != NULL)
		free(arr[j++]);
	free(arr);
}

//-----------------------------------------------------------------------------
//frees elements stored in t_data struct
static void	free_t_data(t_data *all)
{
	if (all->raw_map)
		free_double_char(all->raw_map);
	// if (all->map3d)
	// 	free_double((void *)all->map3d, all->height);
	// if (all->map2d)
	// 	free_double((void *)all->map2d, all->height);
	if (all->north_text)
		free(all->north_text);
	if (all->south_text)
		free(all->south_text);
	if (all->east_text)
		free(all->east_text);
	if (all->west_text)
		free(all->west_text);
	if (all->floor)
		free(all->floor);
	if (all->ceiling)
		free(all->ceiling);
}

void	free_all(t_data *all)
{
	free_t_data(all);
}
