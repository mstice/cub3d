/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:29:21 by mtice             #+#    #+#             */
/*   Updated: 2025/12/12 16:23:51 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//frees a 2d array
void	free_double_char(char **arr)
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
	if (all->north)
		free(all->north);
	if (all->south)
		free(all->south);
	if (all->east)
		free(all->east);
	if (all->west)
		free(all->west);
}

void	free_all(t_data *all)
{
	free_t_data(all);
}
