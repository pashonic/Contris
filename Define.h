//   Contris  Copyright (C) 2009  Aaron Greene

//   This program is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.

//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.

//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef DEFINE_H
#define DEFINE_H

#define CONTROL_PADDING_WIDTH 200
#define CONTROL_PADDING_HEIGHT 50
#define CONTROL_PREVIEW_WIDTH 200
#define CONTROL_PREVIEW_HEIGHT 100
#define CONTROL_BUTTON_WIDTH 150
#define CONTROL_BUTTON_HEIGHT 40
#define CONTROL_BUTTON_BORDER_SIZE 10
#define CONTROL_PREVIEW_SEG 4
#define CONTROL_ITEM_SPACE 10

#define PUZZLE_TILE_SIZE 30
#define PUZZLE_TILE_BORDER 2
#define PUZZLE_SEG_WIDTH 10
#define PUZZLE_SEG_HEIGHT 18
#define PUZZLE_WIDTH (PUZZLE_SEG_WIDTH * PUZZLE_TILE_SIZE)
#define PUZZLE_HEIGHT (PUZZLE_SEG_HEIGHT * PUZZLE_TILE_SIZE)

#define GAME_WIDTH  (PUZZLE_WIDTH + (CONTROL_PADDING_WIDTH * 2))
#define GAME_HEIGHT  (PUZZLE_HEIGHT + (CONTROL_PADDING_HEIGHT * 2))

#define GAME_LINES_TO_LEVEL 10
#define GAME_STARTING_SPEED 1000

typedef unsigned char byte;

enum Tile_Color {LIGHTBLUE, DARKBLUE, ORANGE, YELLOW, GREEN, PURPLE, RED, WHITE};
enum Shape {I_SHAPE, J_SHAPE, L_SHAPE, O_SHAPE, S_SHAPE, T_SHAPE, Z_SHAPE, NO_SHAPE};
struct Color{byte r; byte g; byte b;};

const Color COLOR_Pieces[8] = {{0,255,255}, {0,0,255}, {255,130,0}, {255,255,0}, {0,255,0}, {255,0,255}, {255,0,0}, {255,255,255}};
const Color COLOR_Score_Board = {210, 105, 30};

#endif
