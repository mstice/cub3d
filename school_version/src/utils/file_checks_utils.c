/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:29:45 by mtice             #+#    #+#             */
/*   Updated: 2025/12/12 16:39:59 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
static int	get_colour_values(char *colour)
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
	while (--i >= 0 && n >= 0)
	{
		if (ft_isdigit(colour[i]) && n / 3 == 2)
			blue[n-- % 3] = colour[i];
		else if (ft_isdigit(colour[i]) && n / 3 == 1)
			green[n-- % 3] = colour[i];
		else if (ft_isdigit(colour[i]) && n / 3 == 0)
			red[n-- % 3] = colour[i];
		// else if (!ft_isdigit(colour[i]) && colour[i] != ',' && n)
		// 	return (printf("colour[i]:%d n:%d, i:%d\n", colour[i], n, i), -1);
		while (!ft_isdigit(colour[i]) && n % 3 != 2 && n > 0)
			n--;
	}
	// printf("red: %s\ngreen: %s\nblue: %s\n", red, green, blue);
	return (rgb_to_hex(ft_atoi(red), ft_atoi(green), ft_atoi(blue)));
}

//-----------------------------------------------------------------------------
//records the colours and stores them in the t_data struct
//RETURN_VALUE: returns TRUE if a colour has been found, FALSE if not
bool	record_col(t_data *all, char *p_line, int fd)
{
	bool recorded;

	recorded = true;
	if (ft_strchr(p_line, 'F') && !all->floor)
		all->floor = get_colour_values(p_line);
	else if (ft_strchr(p_line, 'C') && !all->ceiling)
		all->ceiling = get_colour_values(p_line);
	else if ((ft_strchr (p_line, 'F') && all->floor)
			|| (ft_strchr(p_line, 'C') && all->ceiling))
	{
		if (p_line)
			free(p_line);
		close(fd), ft_exit(all, ERR_COL_MANY);
	}
	else
		recorded = false;
	return (recorded);
}

//-----------------------------------------------------------------------------
int	invalid_col(t_data *all)
{
	if (!all->floor)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(ERR_COL_FL, 2), FAILURE);
	else if (!all->ceiling)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(ERR_COL_CL, 2), FAILURE);
	else if (all->floor == -1 || all->ceiling == -1)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(ERR_COL_INV, 2), FAILURE);
	else if (all->floor == WHITE || all->ceiling == WHITE
	 || all->floor == BLACK || all->ceiling == BLACK)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(ERR_COL_BAD, 2), FAILURE);
	else if (all->floor == all->ceiling)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(ERR_COL_DUP, 2), FAILURE);
	return (SUCCESS);
}

//----------------------------------------------------------------------------
static char	*find_text(char *p_line)
{
	char	**path;
	char	*texture;

	path = ft_split(p_line, ' ');
	texture = ft_strdup(path[1]);
	free_double_char(path);
	return (texture);
}

//-----------------------------------------------------------------------------
//records the textures and stores them in the t_data struct
//RETURN_VALUE: returns TRUE if a texture has been found, FALSE if not
bool	record_text(t_data *all, char *p_line, int fd)
{
	bool recorded;

	recorded = true;
	if (!all->north && ft_strnstr(p_line, "NO", ft_strlen(p_line)))
		all->north = find_text(p_line);
	else if (!all->east && ft_strnstr(p_line, "EA", ft_strlen(p_line)))
		all->east = find_text(p_line);
	else if (!all->south && ft_strnstr(p_line, "SO", ft_strlen(p_line)))
		all->south = find_text(p_line);
	else if (!all->west && ft_strnstr(p_line, "WE", ft_strlen(p_line)))
		all->west = find_text(p_line);
	else if (all->north && ft_strnstr(p_line, "NO", ft_strlen(p_line)))
		free(p_line), close(fd), ft_exit(all, ERR_TXT_DUP);
	else if (all->east && ft_strnstr(p_line, "EA", ft_strlen(p_line)))
		free(p_line), close(fd), ft_exit(all, ERR_TXT_DUP);
	else if (all->south && ft_strnstr(p_line, "WE", ft_strlen(p_line)))
		free(p_line), close(fd), ft_exit(all, ERR_TXT_DUP);
	else if (all->west && ft_strnstr(p_line, "SO", ft_strlen(p_line)))
		free(p_line), close(fd), ft_exit(all, ERR_TXT_DUP);
	// else if ((all->north && ft_strnstr(p_line, "NO", ft_strlen(p_line)))
	// 		|| (all->east && ft_strnstr(p_line, "EA", ft_strlen(p_line)))
	// 		|| (all->south && ft_strnstr(p_line, "SO", ft_strlen(p_line)))
	// 		|| (all->west && ft_strnstr(p_line, "WE", ft_strlen(p_line))))
	// {
	// 	if (line)
	// 		free(line);
	// 	if (p_line)
	// 		free(p_line);
	// 	close(fd), ft_exit(all, ERR_TXT_DUP);
	// }
	else
		recorded = false;
	return (recorded);
}

//-----------------------------------------------------------------------------
//checks whether a texture is valid
int	invalid_txt(char *file_name)
{
	int		fd;

	if (!file_name)
		return (ft_putendl_fd(ERR, 2), ft_putendl_fd(ERR_TXT_UND, 2), FAILURE);
	else if (file_invalid_name(file_name, ".xpm"))
	{
		ft_putendl_fd(ERR, 2), ft_putendl_fd(ERR_TXT_NAME, 2);
		return (FAILURE);
	}
	fd = file_no_exist(file_name);
	if (fd == -1)
	{
		ft_putendl_fd(ERR, 2), ft_putendl_fd(ERR_TXT_NOEXIST, 2);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}
