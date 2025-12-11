/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:29:45 by mtice             #+#    #+#             */
/*   Updated: 2025/12/11 18:11:05 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
static unsigned int	char_to_hex(char *colour)
{
	char	red[4];
	char	green[4];
	char	blue[4];
	int		i;
	int		n;

	ft_memset(red, '0', 3);
	ft_memset(green, '0', 3);
	ft_memset(blue, '0', 3);
	red[3] = '\0';
	green[3] = '\0';
	blue[3] = '\0';
	i = ft_strlen(colour);
	n = 8;
	while (--i >= 0)
	{
		if (ft_isdigit(colour[i]) && n / 3 == 2)
			blue[n-- % 3] = colour[i];
		else if (ft_isdigit(colour[i]) && n / 3 == 1)
			green[n-- % 3] = colour[i];
		else if (ft_isdigit(colour[i]) && n / 3 == 0)
			red[n-- % 3] = colour[i];
		while (!ft_isdigit(colour[i]) && n % 3 != 2 && n > 0)
			n--;
	}
	return (rgb_to_hex(ft_atoi(red), ft_atoi(green), ft_atoi(blue)));
}

//-----------------------------------------------------------------------------
//records the colours and stores them in the t_data struct
//RETURN_VALUE: returns TRUE if a colour has been found, FALSE if not
bool	record_col(t_data *all, char *line, char *p_line, int fd)
{
	bool recorded;

	recorded = true;
	if (ft_strchr(p_line, 'F') && !all->floor)
		all->floor = char_to_hex(p_line);
	else if (ft_strchr(p_line, 'C') && !all->ceiling)
		all->ceiling = char_to_hex(p_line);
	else if ((ft_strchr (p_line, 'F') && all->floor)
			|| (ft_strchr(p_line, 'C') && all->ceiling))
	{
		if (line)
			free(line);
		if (p_line)
			free(line);
		close(fd), ft_exit(all, ERR_COL_DUP);
	}
	else
		recorded = false;
	return (recorded);
}

////-----------------------------------------------------------------------------
////checks whether a colour is valid
//int	invalid_col(t_data *all, char *colour)
//{
//	char			**col;
//	unsigned int	hex;
//
//	col = ft_split(colour, ' ');
//	if (!col)
//		return (FAILURE);
//
//	if (!ft_strcmp(col[0], "F"))
//		all->floor = hex;
//	else if (!ft_strcmp(col[0], "C"))
//		all->ceiling = hex;
//	free(colour);
//	free_double_char(col);
//	return (SUCCESS);
//}

//-----------------------------------------------------------------------------
//records the textures and stores them in the t_data struct
//RETURN_VALUE: returns TRUE if a texture has been found, FALSE if not
bool	record_text(t_data *all, char *line, char *p_line, int fd)
{
	bool recorded;

	recorded = true;
	if (ft_strnstr(p_line, "NO", ft_strlen(p_line)) && !all->north_text)
		all->north_text = ft_strdup(p_line);
	else if (ft_strnstr(p_line, "EA", ft_strlen(p_line)) && !all->east_text)
		all->east_text = ft_strdup(p_line);
	else if (ft_strnstr(p_line, "SO", ft_strlen(p_line)) && !all->south_text)
		all->south_text = ft_strdup(p_line);
	else if (ft_strnstr(p_line, "WE", ft_strlen(p_line)) && !all->west_text)
		all->west_text = ft_strdup(p_line);
	else if ((ft_strnstr(p_line, "NO", ft_strlen(p_line)) && all->north_text)
			|| (ft_strnstr(p_line, "EA", ft_strlen(p_line)) && all->east_text)
			|| (ft_strnstr(p_line, "SO", ft_strlen(p_line)) && all->south_text)
			|| (ft_strnstr(p_line, "WE", ft_strlen(p_line)) && all->west_text))
	{
		if (line)
			free(line);
		if (p_line)
			free(p_line);
		close(fd), ft_exit(all, ERR_TXT_DUP);
	}
	else
		recorded = false;
	return (recorded);
}

//-----------------------------------------------------------------------------
//checks whether a texture is valid
//TODO: doesnt recognise incorrect permissions as a separate issue
int	invalid_texture(char *file_name)
{
	int		fd;
	char	**path;

	path = ft_split(file_name, ' ');
	if (!path || !path[0] || !path[1])
		return (free_double_char(path), FAILURE);
	else if (file_invalid_name(path[1], ".xpm"))
		return (free_double_char(path), FAILURE);
	fd = open(path[1], O_RDONLY);
	if (fd < 3 || fd > 1024)
		return (free_double_char(path), FAILURE);
	close(fd);
	free_double_char(path);
	return (SUCCESS);
}
