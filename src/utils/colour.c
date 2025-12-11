/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:38:09 by mtice             #+#    #+#             */
/*   Updated: 2025/12/11 18:11:06 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
char	ft_itoh(int n)
{
	if (n >= 0 && n <= 9)
		return (n + '0');
	else if (n == 10)
		return ('A');
	else if (n == 11)
		return ('B');
	else if (n == 12)
		return ('C');
	else if (n == 13)
		return ('D');
	else if (n == 14)
		return ('E');
	else if (n == 15)
		return ('F');
	else if (n > 15)
	{
		ft_itoh(n % 16);
		ft_itoh(n / 16);
	}
	return (0);
}
//-----------------------------------------------------------------------------
unsigned int	rgb_to_hex(unsigned char r, unsigned char g, unsigned char b)
{
	char	hex[9];
	int		d;

	// if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	// 	ft_exit(all, ERR_COL_INV);
	d = 10000;
	ft_memset(hex, '0', 8);
	hex[1] = 'x';
	hex[2] = ft_itoh(r / 16);
	hex[3] = ft_itoh(((r * d / 16) - (r / 16 * d)) * 16 / d);
	hex[4] = ft_itoh(g / 16);
	hex[5] = ft_itoh(((g * d / 16) - (g / 16 * d)) * 16 / d);
	hex[6] = ft_itoh(b / 16);
	hex[7] = ft_itoh(((b * d / 16) - (b / 16 * d)) * 16 / d);
	hex[8] = '\0';
	return (ft_atoh(hex));
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
