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
#include "Define.h"

namespace System
{
    void DrawPuzzle(SDL_Surface *screen);
    void MovePieceHorizontal(const bool right);
    void MovePieceDown();
    void RotatePiece();
    void Stop();
    void Start();
    void Reset();
    const bool Stopped();
    void Quit();
    const bool Quited();
    const Shape GetNextPiece();
    const int GetNextRotation();
    const int GetScore();
    void SetScore(int value);
    const int GetGameLevel();
    const unsigned int GetGameSpeed();
    void IncrementGameLevel();
    const bool IsGameOver();
    void SetGameOver(const bool state);
}
