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
#include "ShapeData.h"

class Puzzle
{
public:

    Puzzle();
    void Draw(SDL_Surface *screen);
    void Start();
    void Stop();
    void Reset();
    const bool Stopped();
    const Shape GetNextPiece();
    const int GetNextRotation();
    void MoveHorizontal(const bool right);
    void MoveDown();
    void Rotate();

private:
    struct Piece
    {
        Piece(): shape(NO_SHAPE), color(WHITE), rotation(0), x(0), y(0){}
        Shape shape;
        Tile_Color color;
        int rotation;
        int x;
        int y;
    };

    const Shape GetRandomPiece();
    const int GetRandomRotation(Shape shape);
    void SetTileColor(const int x, const int y, Tile_Color color);
    void FindLines();
    void RemoveLine(int line);
    void AddPiece();
    void ClearPuzzle();
    void SetPieceColor(Tile_Color color);
    const bool CollidePiece();
    const bool CollideTile(int x, int y);

    Tile_Color m_tiles[PUZZLE_SEG_WIDTH][PUZZLE_SEG_HEIGHT];
    Piece m_piece;
    Shape m_nextPiece;
    int m_nextRotation;
    bool m_active;
    int m_lineCount;
};
