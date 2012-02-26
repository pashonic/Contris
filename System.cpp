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
#include "System.h"
#include "Puzzle.h"

static Puzzle s_puzzle;
bool GameQuited = false;
int GameScore = 0;
int GameLevel = 1;
unsigned int GameSpeed = GAME_STARTING_SPEED;
bool GameOver = false;

void System::DrawPuzzle(SDL_Surface *screen)
{
    s_puzzle.Draw(screen);
}

void System::MovePieceHorizontal(const bool right)
{
    s_puzzle.MoveHorizontal(right);
}

void System::MovePieceDown()
{
    s_puzzle.MoveDown();
}

void System::RotatePiece()
{
    s_puzzle.Rotate();
}

void System::Stop()
{
    s_puzzle.Stop();
}

void System::Start()
{
    if (GameOver)
    {
        System::Reset();
    }

    s_puzzle.Start();
}

void System::Reset()
{
    GameOver = false;
    GameLevel = 1;
    GameScore = 0;
    GameSpeed = GAME_STARTING_SPEED;
    s_puzzle.Reset();
}

const bool System::Stopped()
{
    return s_puzzle.Stopped();
}

void System::Quit()
{
    GameQuited = true;
}

const bool System::Quited()
{
    return GameQuited;
}

const Shape System::GetNextPiece()
{
    return s_puzzle.GetNextPiece();
}

const int System::GetNextRotation()
{
    return s_puzzle.GetNextRotation();
}

const int System::GetScore()
{
    return GameScore;
}

void System::SetScore(int value)
{
    GameScore = value;
}

void System::IncrementGameLevel()
{
    GameLevel++;
    GameSpeed = static_cast<int>(GameSpeed * .8);
}

const unsigned int System::GetGameSpeed()
{
    return GameSpeed;
}

const int System::GetGameLevel()
{
    return GameLevel;
}

const bool System::IsGameOver()
{
    return GameOver;
}

void System::SetGameOver(bool state)
{
    GameOver = state;
}
