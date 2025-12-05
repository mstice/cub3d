/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:25:59 by mtice             #+#    #+#             */
/*   Updated: 2025/12/05 14:30:36 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define SUCCESS 0
# define FAILURE 1
# define SUB 26

//------------------------------COLOURS----------------------------------------
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xF60000
# define ORANGE 0xFF8C00
# define YELLOW 0xFFEE00
# define GREEN 0x4DE94C
# define BLUE 0x3783FF
# define PURPLE 0x4815AA

//-----------------------------WINDOW SETTINGS---------------------------------
# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000
# define SKY_HEIGHT 200
# define FLOOR_HEIGHT 200
# define WIN_NAME "cub3D"

//----------------------------MLX HOOK VARIABLES-------------------------------
# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

# define NO_EVENT_MASK "0L"
# define KEY_PRESS_MASK "1L<<0"
# define KEY_RELEASE_MASK "1L<<1"
# define BUTTON_PRESS_MASK "1L<<2"
# define BUTTON_RELEASE_MASK "1L<<3"
# define ENTER_WINDOW_MASK "1L<<4"
# define LEAVE_WINDOW_MASK "1L<<5"

//-----------------------------------KEYCODES----------------------------------
# define ESC_KEY 65307
# define W_KEY 
# define A_KEY
# define S_KEY
# define D_KEY
# define UP_KEY 65364
# define DOWN_KEY 65362
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define SPACE_KEY 32
# define MOUSE_KEY 

//---------------------------------ERROR MESSAGES------------------------------
# define ERR "Error"
# define ERR_USAGE "Usage: ./cub3D <map.cub>"
# define ERR_FILE_NAME "Invalid file name. Expected <map.cub>"
# define ERR_FILE_NOEXIST "File does not exist or has no read permissions"
# define ERR_FILE_EMPTY "File is empty"
# define ERR_FILE_OPEN "Could not open file"
# define ERR_FILE_INV "Invalid file"
# define ERR_NO_TEXT "One or more textures not defined. Use: <NO/SO/WE/EA ./path>"
# define ERR_PATH_TEXT "Invalid path to texture. Usage: <WO ./path>"
# define ERR_DUP_TEXT "Duplicate textures"
# define ERR_XPM_TEXT "Texture paths must lead to .xpm file"
# define ERR_COL "Ceiling or floor colour not defined. Usage: <F/C 20, 10, 30>"
# define ERR_INV_COL "Colour is invalid. Pick a range from 0 to 255"
# define ERR_WALLS "Map is not surrounded by walls"
# define ERR_NO_POS "Player spawn position on map not specified"
# define ERR_MANY_POS "Too many player spawn positions specified on map"
# define ERR_INV_EL "Invalid element found in file"

# define ERR_MALLOC "Malloc error"

#endif
