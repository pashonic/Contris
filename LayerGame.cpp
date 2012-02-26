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
#include "LayerGame.h"

LayerGame::LayerGame(): m_puzzleSurface(0), m_timeTick(0)
{
    m_puzzleSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, PUZZLE_WIDTH, PUZZLE_HEIGHT,  32, 0, 0, 0, 0);
}

void LayerGame::HandleEvent(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && !System::IsGameOver())
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_UP:
                System::RotatePiece();
                return;
            case SDLK_DOWN:
                System::MovePieceDown();
                return;
            case SDLK_LEFT:
                System::MovePieceHorizontal(false);
                return;
            case SDLK_RIGHT:
                System::MovePieceHorizontal(true);
                return;
            default:
                break;
        }
    }
}

void LayerGame::Draw(SDL_Surface *screen)
{
    //
    // If game over draw "game over" else the puzzle.
    //

    if (System::IsGameOver())
    {
        DrawGameOver(m_puzzleSurface);
    }
    else
    {
        System::DrawPuzzle(m_puzzleSurface);
    }

    //
    // Apply puzzle surface to main surface.
    //

    ApplySurface((screen->clip_rect.w - m_puzzleSurface->clip_rect.w)/2,
                 (screen->clip_rect.h - m_puzzleSurface->clip_rect.h)/2,
                  m_puzzleSurface,
                  screen);

    //
    // Check drop timer.
    //

    if ((SDL_GetTicks() - m_timeTick) > System::GetGameSpeed() && !System::IsGameOver())
    {
        System::MovePieceDown();
        m_timeTick = SDL_GetTicks();
    }
}

void LayerGame::DrawGameOver(SDL_Surface *screen)
{
    //
    // Fill puzzle surface with grey.
    //

    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 75, 75, 75));

    //
    // Create text.
    //

    TTF_Font *font = TTF_OpenFont("Verdana.ttf", 40);
    SDL_Color textColor = {COLOR_Score_Board.r, COLOR_Score_Board.g, COLOR_Score_Board.b};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Game Over", textColor);

    //
    // Calculate text placement and draw to puzzle surface.
    //

    const int x = (screen->clip_rect.w - textSurface->clip_rect.w)/2;
    const int y = (screen->clip_rect.h - textSurface->clip_rect.h)/2 - textSurface->clip_rect.h;
    ApplySurface(x, y, textSurface, screen);

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

LayerGame::~LayerGame()
{
    if (m_puzzleSurface != 0)
    {
        SDL_FreeSurface(m_puzzleSurface);
    }
}
