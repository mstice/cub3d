/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:25:59 by mtice             #+#    #+#             */
/*   Updated: 2026/01/30 15:39:04 by ombatkam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define SUCCESS 0
# define FAILURE 1

//------------------------------COLOURS----------------------------------------
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xF60000
# define ORANGE 0xFF8C00
# define YELLOW 0xFFEE00
# define GREEN 0x4DE94C
# define BLUE 0x3783FF
# define SKY 0x87CEEB
# define PURPLE 0x4815AA
# define BROWN 0x964B00

//-----------------------------WINDOW SETTINGS---------------------------------
# define WIN_WIDTH 600
# define WIN_HEIGHT 600
# define WIN_NAME "cub3D"

//----------------------------MLX HOOK VARIABLES-------------------------------
# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

//---------------------------------ERROR MESSAGES------------------------------
# define ERR "Error"
# define ERR_MALLOC "Malloc error"
# define ERR_USAGE "Usage: ./cub3D <file.cub>"
# define ERR_FILE_NAME "Invalid file name. Expected <file.cub>"
# define ERR_FILE_NOEXIST "File does not exist or has no read permissions"
# define ERR_FILE_EMPTY "File is empty"
# define ERR_FILE_INV "Invalid element found in file"
# define ERR_TXT_UND "One or more textures undefined. Use:<NO path/texture.xpm>"
# define ERR_TXT_NOEXIST "A texture does not exist or has no read permissions"
# define ERR_TXT_PATH "Invalid path to texture. Use: <WO path/to/texture.xpm>"
# define ERR_TXT_DUP "Duplicate textures. All textures must be unique"
# define ERR_TXT_MANY "Too many textures defined"
# define ERR_TXT_NAME "Invalid texture name. Expected <file.xpm>"
# define ERR_COL_CL "Ceiling colour not properly defined. Usage: <C 0,170,200>"
# define ERR_COL_FL "Floor colour not properly defined. Usage: <F 120,52,5>"
# define ERR_COL_DUP "Ceiling and floor colours are the same"
# define ERR_COL_INV "Some RGB values are invalid or undefined. Range: 0 to 255"
# define ERR_COL_BAD "Ceiling or floor colour cannot be pure black or white"
# define ERR_COL_MANY "More than one ceiling or floor colour defined"
# define ERR_MAP_S "Map is too small. Usage: height > 2 && width > 2"
# define ERR_MAP_WAL "Map is not surrounded by walls"
# define ERR_MAP_LAST "Map must be the last content in file"
# define ERR_POS_NOEXIST "Player spawn position on map not specified"
# define ERR_POS_DUP "Too many player spawn positions specified on map"
# define ERR_MLX "Minilibx error"

//----------------------------------MAP MACROS---------------------------------
# define FOV 0.66
# define ANGLE 18
# define MOVE_SPEED 0.125
# define ROT_SPEED 0.15
# define TXT_SIZE 64

# define ERR_BOUNDS "Tried to draw map out of bounds"

#endif
