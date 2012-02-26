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

#include "Pch.h"
#include "Preview.h"
#include "ShapeData.h"

Preview::Preview(): m_x(0), m_y(0)
{
    ClearPreview();
}

void Preview::SetTileColor(const int x, const int y, const Tile_Color color)
{
    m_tiles[x][y] = color;
}

void Preview::Draw(SDL_Surface *screen)
{

    const Shape nextShape = System::GetNextPiece();
    const int nextRotation = System::GetNextRotation();
    const Tile_Color nextColor = static_cast<Tile_Color>(nextShape);
    const int keyTileX = 2;
    const int keyTileY = 1;

    //
    // Set Piece color.
    //

    ClearPreview();
    SetTileColor(keyTileX, keyTileY, nextColor);
    for (int i = 0; i < 3; i++)
    {
        SetTileColor(keyTileX + Piece_Data[nextShape].rotations[nextRotation].state[i][0],
                     keyTileY + Piece_Data[nextShape].rotations[nextRotation].state[i][1],
                     nextColor);
    }

    //
    // Fill puzzle surface with white.
    //

    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 255, 255));
    for (int x = 0; x < CONTROL_PREVIEW_SEG; x++)
    {
        for (int y = 0; y < CONTROL_PREVIEW_SEG; y++)
        {
            if (m_tiles[x][y] == WHITE)
            {
                continue;
            }

            const int squareWidth = screen->clip_rect.w / CONTROL_PREVIEW_SEG;
            const int squareHeight = screen->clip_rect.h / CONTROL_PREVIEW_SEG;
            const int xTileCord = x * squareWidth;
            const int yTileCord = y * squareWidth;

            SDL_Rect border_Rect;
            border_Rect.w = squareWidth + PUZZLE_TILE_BORDER;
            border_Rect.h = squareHeight + PUZZLE_TILE_BORDER;
            border_Rect.x = xTileCord - PUZZLE_TILE_BORDER;
            border_Rect.y = yTileCord - PUZZLE_TILE_BORDER;

            SDL_FillRect(screen, &border_Rect, SDL_MapRGB(screen->format, 0, 0, 0));

            SDL_Rect tile_Rect;
            tile_Rect.w = squareWidth - PUZZLE_TILE_BORDER;
            tile_Rect.h = squareHeight - PUZZLE_TILE_BORDER;
            tile_Rect.x = xTileCord;
            tile_Rect.y = yTileCord;

            SDL_FillRect(screen, &tile_Rect, SDL_MapRGB(screen->format, COLOR_Pieces[m_tiles[x][y]].r,
                                                                        COLOR_Pieces[m_tiles[x][y]].g,
                                                                        COLOR_Pieces[m_tiles[x][y]].b));
        }
    }
}

void Preview::SetPosition(const int x, const int y)
{
    m_x = x;
    m_y = y;
}
const int Preview::GetX()
{
    return m_x;
}

const int Preview::GetY()
{
    return m_y;
}

void Preview::ClearPreview()
{
    for (int x = 0; x < CONTROL_PREVIEW_SEG; x++)
    {
        for (int y = 0; y < CONTROL_PREVIEW_SEG; y++)
        {
            SetTileColor(x, y, WHITE);
        }
    }
}
