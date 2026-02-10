/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:26:22 by mtice             #+#    #+#             */
/*   Updated: 2025/12/12 16:39:59 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//checks if map is populated
//records height and maximum width of the map
//stores this information in the t_data struct
void	record_map_attributes(t_data *all, int fd, char *map_start)
{
	char	*line;

	line = ft_strtrim(map_start, "\n");
	while (!line || !(*line))
	{
		free(line);
		line = get_next_line(fd);
		line = ft_strtrim(line, "\n");
		all->map_start++;
	}
	while (line)
	{
		all->height++;
		all->width = get_max(all->width, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		line = ft_strtrim(line, "\n");
	}
	if (all->height == 0 || all->width == 0)
		ft_exit(all, ERR_MAP_LAST, 0);
	else if (all->height < 3 || all->width < 3)
		ft_exit(all, ERR_MAP_S, fd);
}

//-----------------------------------------------------------------------------
//checks if any elements are out of order
//e.g. no player, too many players, and non-accepted elements
static void	map_err_elements(t_data *all)
{
	int		j;
	int		i;

	j = 0;
	while (all->map[j] != NULL)
	{
		i = 0;
		while (all->map[j][i] != '\0')
		{
			if (all->map[j][i] == 'N' || all->map[j][i] == 'E'
				|| all->map[j][i] == 'S' || all->map[j][i] == 'W')
			{
				if (all->player != NOPLAYER)
					ft_exit(all, ERR_POS_DUP, 0);
				all->player = all->map[j][i];
			}
			if (!accepted(all->map[j][i]))
				ft_exit(all, ERR_FILE_INV, 0);
			i++;
		}
		j++;
	}
	if (all->player == NOPLAYER)
		ft_exit(all, ERR_POS_NOEXIST, 0);
}

//-----------------------------------------------------------------------------
//checks if open areas are surrounded by walls from a horizontal pov
static void	map_err_walls_horizontal(t_data *all, t_area area)
{
	int		j;
	int		i;

	j = 0;
	while (all->map[j] != NULL)
	{
		i = 0;
		area = UNDEFINED;
		while (all->map[j][i] != '\0')
		{
			if (is_wall(all->map[j][i]))
				area = WALL;
			else if (is_open(all->map[j][i]) && area != UNDEFINED)
				area = OPEN;
			else if (is_open(all->map[j][i]) && area == UNDEFINED)
				ft_exit(all, ERR_MAP_WAL, 0);
			i++;
		}
		if (area != WALL)
			ft_exit(all, ERR_MAP_WAL, 0);
		j++;
	}
	if (area != WALL)
		ft_exit(all, ERR_MAP_WAL, 0);
}

//-----------------------------------------------------------------------------
//checks if open areas are surrounded by walls from a vertical pov
static void	map_err_walls_vertical(t_data *all, t_area area)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (all->map[j] != NULL)
	{
		area = UNDEFINED;
		while (all->map[j] != NULL && all->map[j][i] != '\0')
		{
			if (is_wall(all->map[j][i]))
				area = WALL;
			else if (is_open(all->map[j][i]) && area != UNDEFINED)
				area = OPEN;
			else if (is_open(all->map[j][i]) && area == UNDEFINED)
				ft_exit(all, ERR_MAP_WAL, 0);
			safe_j(all, &j, i);
		}
		if (area != WALL)
			ft_exit(all, ERR_MAP_WAL, 0);
		safe_j(all, &j, ++i);
	}
	if (area != WALL)
		ft_exit(all, ERR_MAP_WAL, 0);
}

//-----------------------------------------------------------------------------
//parses map and performs necessary error checking before rendering images
//TODO: empty line in map SHOULD be a problem. HANDLE THIS!
int	map_checks(t_data *all, char *map_name)
{
	create_map(all, map_name);
	map_err_elements(all);
	map_err_walls_horizontal(all, UNDEFINED);
	map_err_walls_vertical(all, UNDEFINED);
	reformat_map(all);
	return (SUCCESS);
}
