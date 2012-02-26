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
#include "AppContris.h"

AppContris::AppContris(): m_screen(0)
{

}

const bool AppContris::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }

    if(TTF_Init() == -1)
    {
        return false;
    }

    m_screen = SDL_SetVideoMode(GAME_WIDTH, GAME_HEIGHT, 32, SDL_SWSURFACE);
    if (m_screen == NULL)
    {
        return false;
    }

    if (!m_layerControl.Init())
    {
        return false;
    }

    SDL_WM_SetCaption("Contris", NULL);

    return true;
}

void AppContris::Run()
{

    if (!Init())
    {
        CleanUp();
        return;
    }

    SDL_Event event;

    while(true)
    {

        //
        // Process events.
        //

        while(SDL_PollEvent(&event))
        {
            m_layerControl.HandleEvent(event);
            m_layerGame.HandleEvent(event);
        }

        //
        // Check for button quit, we want to pause before quiting to show button was clicked.
        //

        if (System::Quited())
        {
            static int time = SDL_GetTicks();
            if ((SDL_GetTicks() - time) > 300)
            {
                break;
            }
        }

        //
        // Check for forced quit, the user clicked on Window "X" to quit.
        //

        if (event.type == SDL_QUIT)
        {
            break;
        }

        //
        // Paint black to entire screen.
        //

        SDL_FillRect(m_screen, &m_screen->clip_rect, SDL_MapRGB(m_screen->format, 0, 0, 0));

        //
        // Draw layers to screen.
        //

        m_layerControl.Draw(m_screen);
        m_layerGame.Draw(m_screen);
        SDL_Flip(m_screen);
    }

    CleanUp();
}

void AppContris::CleanUp()
{
    SDL_FreeSurface(m_screen);
    SDL_Quit();
    TTF_Quit();
}
