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

#pragma once

class Preview
{
public:
    Preview();
    void Draw(SDL_Surface *screen);
    void SetPosition(const int x, const int y);
    const int GetX();
    const int GetY();

private:
    void SetTileColor(const int x, const int y, const Tile_Color color);
    void ClearPreview();

    Tile_Color m_tiles[CONTROL_PREVIEW_SEG][CONTROL_PREVIEW_SEG];
    int m_x;
    int m_y;
};
