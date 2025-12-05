/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:38:09 by mtice             #+#    #+#             */
/*   Updated: 2025/12/05 15:42:12 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
char	*rgb_to_hex(unsigned char r, unsigned char g, unsigned char b)
{
	char	*hex;

	hex = ft_calloc(sizeof(char), 8 + 1);
	return (hex);
}

//-----------------------------------------------------------------------------
unsigned int	ft_atoh(const char *nptr)
{
	int		number;
	char	c;
	int		i;

	number = 0;
	i = 0;
	if (nptr[i] == '0' && (nptr[i + 1] == 'x' || nptr[i + 1] == 'X'))
		i += 2;
	else
		return (0);
	while (nptr[i] != ' ' && nptr[i] != '\0')
	{
		c = ft_tolower(nptr[i]);
		if (c >= '0' && c <= '9')
			number = number * 16 + (c - '0');
		else if (c >= 'a' && c <= 'f')
			number = number * 16 + (c - 'a' + 10);
		else
			break ;
		i++;
	}
	return (number);
}
