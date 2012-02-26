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
#include "Button.h"

Button::Button(): m_label(0), m_clickTimer(0), m_x(0), m_y(0)
{

}

void Button::Draw(SDL_Surface *screen)
{
    //
    // Check for button click.
    //

    Color bgColor = {139, 134, 130};
    if ((SDL_GetTicks() - m_clickTimer) < 100)
    {
        bgColor.r = 255;
        bgColor.g = 0;
        bgColor.b = 0;
    }

    //
    // Draw background.
    //

    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, bgColor.r, bgColor.g, bgColor.b));

    SDL_Rect foreground_Rect;
    foreground_Rect.w = screen->clip_rect.w - CONTROL_BUTTON_BORDER_SIZE;
    foreground_Rect.h = screen->clip_rect.h - CONTROL_BUTTON_BORDER_SIZE;
    foreground_Rect.x = (screen->clip_rect.w - foreground_Rect.w)/2;
    foreground_Rect.y = (screen->clip_rect.h - foreground_Rect.h)/2;

    //
    // Draw foreground.
    //

    SDL_FillRect(screen, &foreground_Rect, SDL_MapRGB(screen->format, 220, 220, 220));

    //
    // Draw label if its set.
    //

    if (m_label != 0)
    {
        ApplySurface((screen->w - m_label->w)/2, (screen->h - m_label->h)/2, m_label, screen);
    }
}

void Button::SetLabel(const char *label)
{
    if (m_label != 0)
    {
        SDL_FreeSurface(m_label);
    }

    TTF_Font *font = TTF_OpenFont("Verdana.ttf", 20);
    SDL_Color textColor = {COLOR_Score_Board.r, COLOR_Score_Board.g, COLOR_Score_Board.b};
    m_label = TTF_RenderText_Solid(font, label, textColor);
    TTF_CloseFont(font);
}

void Button::Click()
{
    m_clickTimer = SDL_GetTicks();
}

void Button::SetPosition(const int x, const int y)
{
    m_x = x;
    m_y = y;
}
const int Button::GetX()
{
    return m_x;
}

const int Button::GetY()
{
    return m_y;
}

Button::~Button()
{
    if (m_label != 0)
    {
        SDL_FreeSurface(m_label);
    }
}
