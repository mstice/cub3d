/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:38:09 by mtice             #+#    #+#             */
/*   Updated: 2025/12/12 16:21:21 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
static char	ft_itoh(int n)
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
static unsigned int	ft_atoh(const char *nptr)
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

//-----------------------------------------------------------------------------
unsigned int	rgb_to_hex(unsigned char r, unsigned char g, unsigned char b)
{
	char	hex[9];
	int		d;

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
int	collect_rgb(char *colour, char r[4], char g[4], char b[4])
{
	int		i;
	int		n;

	i = ft_strlen(colour);
	n = 8;
	while (--i >= 0 && n >= 0)
	{
		if (ft_isdigit(colour[i]) && n / 3 == 2)
			b[n-- % 3] = colour[i];
		else if (ft_isdigit(colour[i]) && n / 3 == 1)
			g[n-- % 3] = colour[i];
		else if (ft_isdigit(colour[i]) && n / 3 == 0)
			r[n-- % 3] = colour[i];
		else if (!ft_isdigit(colour[i]) && colour[i] != ','
			&& colour[i] != ' ' && n)
			return (-2);
		while (!ft_isdigit(colour[i]) && n % 3 != 2 && n)
			n--;
	}
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
int	get_colour_values(char *colour)
{
	char	r[4];
	char	g[4];
	char	b[4];

	ft_memset(r, '0', 3);
	ft_memset(g, '0', 3);
	ft_memset(b, '0', 3);
	r[3] = '\0';
	g[3] = '\0';
	b[3] = '\0';
	if (collect_rgb(colour, r, g, b) != SUCCESS)
		return (-2);
	if (ft_strncmp(r, "255\0", 4) > 0 || ft_strncmp(g, "255\0", 4) > 0
		|| ft_strncmp(b, "255\0", 4) > 0)
		return (-2);
	return (rgb_to_hex(ft_atoi(r), ft_atoi(g), ft_atoi(b)));
}
