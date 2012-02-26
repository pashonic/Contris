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
#include "Button.h"
#include "Preview.h"

class LayerControl
{
public:
    LayerControl();
    ~LayerControl();
    const bool Init();
    void Draw(SDL_Surface *screen);
    void HandleEvent(SDL_Event &event);

private:
    const bool ButtonClicked(const int x, const int y, Button &button);
    void DrawScoreBoard(SDL_Surface *screen);
    const int GetXScoreBoardItem(const SDL_Surface *surface);

    SDL_Surface *m_startButtonSurface;
    SDL_Surface *m_resetButtonSurface;
    SDL_Surface *m_exitButtonSurface;
    SDL_Surface *m_previewSurface;

    Button m_startButton;
    Button m_resetButton;
    Button m_exitButton;
    Preview m_preview;
};
