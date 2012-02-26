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
#include "Puzzle.h"

Puzzle::Puzzle(): m_active(false), m_lineCount(0)
{
    srand((unsigned)time(0));
    ClearPuzzle();

    m_nextPiece = GetRandomPiece();
    m_nextRotation = GetRandomRotation(m_nextPiece);
}

void Puzzle::SetTileColor(const int x, const int y, Tile_Color color)
{
    m_tiles[x][y] = color;
}

void Puzzle::Draw(SDL_Surface *screen)
{

    //
    // Fill puzzle surface with white.
    //

    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 255, 255));

    //
    // Set piece tiles.
    //

    if (m_active)
    {
        SetPieceColor(m_piece.color);
    }

    //
    // Draw entire puzzle.
    //

    for (int x = 0; x < PUZZLE_SEG_WIDTH; x++)
    {
        for (int y = 0; y < PUZZLE_SEG_HEIGHT; y++)
        {
            if (m_tiles[x][y] == WHITE)
            {
                continue;
            }

            const int squareWidth = screen->clip_rect.w / PUZZLE_SEG_WIDTH;
            const int squareHeight = screen->clip_rect.h / PUZZLE_SEG_HEIGHT;
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

void Puzzle::AddPiece()
{
    m_piece.shape = m_nextPiece;
    m_piece.color = static_cast<Tile_Color>(m_nextPiece);
    m_piece.rotation = m_nextRotation;
    m_piece.x = PUZZLE_SEG_WIDTH / 2;
    m_piece.y = 1;

    if (m_tiles[m_piece.x][m_piece.y] != WHITE)
    {
        Stop();
        System::SetGameOver(true);
    }

    m_nextPiece = GetRandomPiece();
    m_nextRotation = GetRandomRotation(m_nextPiece);
}

const Shape Puzzle::GetRandomPiece()
{
    const int piece = rand() % 7;
    return static_cast<Shape>(piece);
}

const int Puzzle::GetRandomRotation(Shape shape)
{
    return rand() % (Piece_Data[static_cast<int>(shape)].rotation_Count);
}

void Puzzle::FindLines()
{

    //
    // Find lines with no empty tiles.
    //

    int lines = 0;
    for (int y = 0; y < PUZZLE_SEG_HEIGHT; y++)
    {
        for (int x = 0; x < PUZZLE_SEG_WIDTH; x++)
        {
            if (m_tiles[x][y] == WHITE)
            {
                break;
            }

            if (x > PUZZLE_SEG_WIDTH - 2)
            {
                lines++;
                RemoveLine(y);
            }
        }
    }

    //
    // Add to game score and keep count so we know when to increase level.
    //

    if (lines > 0)
    {
        m_lineCount+=lines;
        System::SetScore(System::GetScore() + (lines * lines));
    }

    //
    // Check if it is time to increase game level.
    //

    if (m_lineCount >= GAME_LINES_TO_LEVEL)
    {
        System::IncrementGameLevel();

        if (m_lineCount > GAME_LINES_TO_LEVEL)
        {
            m_lineCount = m_lineCount - GAME_LINES_TO_LEVEL;
        }
        else
        {
            m_lineCount = 0;
        }
    }
}

void Puzzle::RemoveLine(int line)
{
    for (int y = line; y > 0; y--)
    {
        for (int x = 0; x < PUZZLE_SEG_WIDTH; x++)
        {
            m_tiles[x][y] = m_tiles[x][y - 1];
        }
    }
}

void Puzzle::MoveHorizontal(const bool right)
{
    if (!m_active)
    {
        return;
    }

    SetPieceColor(WHITE);
    int direction = (right?1:-1);
    m_piece.x += direction;

    if (CollidePiece())
    {
        m_piece.x += direction * -1;
    }
}

void Puzzle::MoveDown()
{
    if (!m_active)
    {
        return;
    }

    Tile_Color tempColor = m_tiles[m_piece.x][m_piece.y];
    SetPieceColor(WHITE);
    m_piece.y++;

    if (CollidePiece())
    {
        m_piece.y--;
        SetPieceColor(tempColor);
        FindLines();
        AddPiece();
    }
}

void Puzzle::Rotate()
{
    if (!m_active)
    {
        return;
    }

    SetPieceColor(WHITE);
    const int preRot = m_piece.rotation;

    if (m_piece.rotation >= Piece_Data[m_piece.shape].rotation_Count - 1)
    {
        m_piece.rotation = 0;
    }
    else
    {
        m_piece.rotation++;
    }

    if (CollidePiece())
    {
        m_piece.rotation = preRot;
    }
}

void Puzzle::ClearPuzzle()
{
    m_piece.shape = NO_SHAPE;

    for (int x = 0; x < PUZZLE_SEG_WIDTH; x++)
    {
        for (int y = 0; y < PUZZLE_SEG_HEIGHT; y++)
        {
            SetTileColor(x, y, WHITE);
        }
    }
}

void Puzzle::SetPieceColor(Tile_Color color)
{
    SetTileColor(m_piece.x, m_piece.y, color);

    for (int i = 0; i < 3; i++)
    {
        SetTileColor(m_piece.x + Piece_Data[m_piece.shape].rotations[m_piece.rotation].state[i][0],
                     m_piece.y + Piece_Data[m_piece.shape].rotations[m_piece.rotation].state[i][1],
                     color);
    }
}

const bool Puzzle::CollidePiece()
{
    if (CollideTile(m_piece.x, m_piece.y))
    {
        return true;
    }

    for (int i = 0; i < 3; i++)
    {
        if (CollideTile(m_piece.x + Piece_Data[m_piece.shape].rotations[m_piece.rotation].state[i][0],
                        m_piece.y + Piece_Data[m_piece.shape].rotations[m_piece.rotation].state[i][1]))
        {
            return true;
        }
    }

    return false;
}

const bool Puzzle::CollideTile(int x, int y)
{
    if (x >= PUZZLE_SEG_WIDTH || x < 0)
    {
        return true;
    }

    if (y >= PUZZLE_SEG_HEIGHT)
    {
        return true;
    }

    if (m_tiles[x][y] != WHITE)
    {
        return true;
    }

    return false;
}

const Shape Puzzle::GetNextPiece()
{
    return m_nextPiece;
}

const int Puzzle::GetNextRotation()
{
    return m_nextRotation;
}

void Puzzle::Start()
{
    if (!m_active)
    {
        if (m_piece.shape == NO_SHAPE)
        {
            AddPiece();
        }

        m_active = true;
    }
}

void Puzzle::Stop()
{
    m_active = false;
}

void Puzzle::Reset()
{
    ClearPuzzle();
    m_active = false;
    m_lineCount = 0;
}

const bool Puzzle::Stopped()
{
   return !m_active;
}
