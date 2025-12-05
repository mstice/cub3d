/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:07:34 by mtice             #+#    #+#             */
/*   Updated: 2025/12/05 13:50:23 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//returns true if char c is an accepted element of the map
bool	accepted(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W'
		|| c == ' ')
		return (true);
	else
		return (false);
}

//-----------------------------------------------------------------------------
//returns true if char c is an element that represents a wall
bool	is_wall(char c)
{
	if (c == '1')
		return (true);
	else
		return (false);
}

//-----------------------------------------------------------------------------
//returns true if char c is an element that represents open space
bool	is_open(char c)
{
	if (c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (true);
	else
		return (false);
}

//-----------------------------------------------------------------------------
//function that determines the "safe" value of j used to check walls vertically
//since lines have different lengths, it is not always possible to iterate j
//while i remains constant
void	safe_j(t_data *all, int *j, int i)
{
	int	k;

	k = 0;
	if (*j < all->height)
	{
		k = *j + 1;
		while (k < all->height && i >= ft_strlen(all->raw_map[k]))
			k++;
		*j = k;
	}
	else if (*j == all->height)
	{
		while (k < all->height && i >= ft_strlen(all->raw_map[k]))
			k++;
		*j = k;
	}
}


