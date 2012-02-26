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
#include "LayerControl.h"

LayerControl::LayerControl(): m_startButtonSurface(0),
                              m_resetButtonSurface(0),
                              m_exitButtonSurface(0),
                              m_previewSurface(0)
{
    m_startButtonSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, CONTROL_BUTTON_WIDTH, CONTROL_BUTTON_HEIGHT,  32, 0, 0, 0, 0);
    m_resetButtonSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, CONTROL_BUTTON_WIDTH, CONTROL_BUTTON_HEIGHT,  32, 0, 0, 0, 0);
    m_exitButtonSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, CONTROL_BUTTON_WIDTH, CONTROL_BUTTON_HEIGHT,  32, 0, 0, 0, 0);
    m_previewSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, (CONTROL_PREVIEW_SEG * PUZZLE_TILE_SIZE), (CONTROL_PREVIEW_SEG * PUZZLE_TILE_SIZE),  32, 0, 0, 0, 0);
}

LayerControl::~LayerControl()
{
    SDL_FreeSurface(m_startButtonSurface);
    SDL_FreeSurface(m_resetButtonSurface);
    SDL_FreeSurface(m_exitButtonSurface);
    SDL_FreeSurface(m_previewSurface);
}

const bool LayerControl::Init()
{

    //
    // Set preview position.
    //

    const int previewX = (PUZZLE_WIDTH + (CONTROL_PADDING_WIDTH)) + (((CONTROL_PADDING_WIDTH) - m_previewSurface->clip_rect.w)/2);
    m_preview.SetPosition(previewX , (CONTROL_PADDING_HEIGHT));

    //
    // Set button positions on screen.
    //

    const int buttonX = ((CONTROL_PADDING_WIDTH) - CONTROL_BUTTON_WIDTH)/2;
    const int buttonY = (CONTROL_PADDING_HEIGHT);
    m_startButton.SetPosition(buttonX, buttonY);
    m_resetButton.SetPosition(buttonX, buttonY + CONTROL_BUTTON_HEIGHT + 10);
    m_exitButton.SetPosition(buttonX, buttonY + (CONTROL_BUTTON_HEIGHT + 10) * 2);

    //
    // Set initial labels.
    //

    m_startButton.SetLabel("Start");
    m_resetButton.SetLabel("Reset");
    m_exitButton.SetLabel("Exit");

    return true;
}

void LayerControl::HandleEvent(SDL_Event &event)
{
    if (event.type != SDL_MOUSEBUTTONDOWN || event.button.button != SDL_BUTTON_LEFT)
    {
        return;
    }

    //
    // Start/Stop button click.
    //

    if (ButtonClicked(event.button.x, event.button.y, m_startButton))
    {
        if (System::Stopped())
        {
            System::Start();
            m_startButton.SetLabel("Stop");
        }
        else
        {
            System::Stop();
            m_startButton.SetLabel("Start");
        }
        m_startButton.Click();
    }

    //
    // Reset button click.
    //

    else if (ButtonClicked(event.button.x, event.button.y, m_resetButton))
    {
        System::Reset();
        m_resetButton.Click();
        m_startButton.SetLabel("Start");
    }

    //
    // Exit button click.
    //

    else if (ButtonClicked(event.button.x, event.button.y, m_exitButton))
    {
        System::Quit();
        m_exitButton.Click();
    }
}


void LayerControl::Draw(SDL_Surface *screen)
{

    if (System::IsGameOver())
    {
        m_startButton.SetLabel("Start");
    }

    //
    // Draw Start/Stop Button.
    //

    m_startButton.Draw(m_startButtonSurface);
    ApplySurface(m_startButton.GetX(), m_startButton.GetY(), m_startButtonSurface, screen);

    //
    // Draw Pause button.
    //

    m_resetButton.Draw(m_resetButtonSurface);
    ApplySurface(m_resetButton.GetX(), m_resetButton.GetY(), m_resetButtonSurface, screen);

    //
    // Draw Exit button.
    //

    m_exitButton.Draw(m_exitButtonSurface);
    ApplySurface(m_exitButton.GetX(), m_exitButton.GetY(), m_exitButtonSurface, screen);

    //
    // Draw preview.
    //

    m_preview.Draw(m_previewSurface);
    ApplySurface(m_preview.GetX(), m_preview.GetY(), m_previewSurface, screen);

    //
    // Draw score.
    //

    DrawScoreBoard(screen);
}

void LayerControl::DrawScoreBoard(SDL_Surface *screen)
{
    TTF_Font *font = TTF_OpenFont("Verdana.ttf", 24);
    SDL_Color textColor = {COLOR_Score_Board.r, COLOR_Score_Board.g, COLOR_Score_Board.b};

    //
    // Create surfaces.
    //

    SDL_Surface *scoreLabelSurface = TTF_RenderText_Solid(font, "SCORE:", textColor);
    SDL_Surface *levelLabelSurface = TTF_RenderText_Solid(font, "LEVEL:", textColor);

    char bufferScoreValue[100];
	sprintf(bufferScoreValue, "%i", System::GetScore());
    SDL_Surface *scoreValueSurface = TTF_RenderText_Solid(font, bufferScoreValue, textColor);

    char bufferLevelValue[100];
	sprintf(bufferLevelValue, "%i", System::GetGameLevel());
    SDL_Surface *levelValueSurface = TTF_RenderText_Solid(font, bufferLevelValue, textColor);

    //
    // Set static positions.
    //

    const int startY = (CONTROL_PADDING_HEIGHT) + (CONTROL_PREVIEW_SEG * PUZZLE_TILE_SIZE) + 10;
    const int textHeight = scoreLabelSurface->clip_rect.h + CONTROL_ITEM_SPACE;

    //
    // Draw score board items to screen.
    //

    ApplySurface(GetXScoreBoardItem(scoreLabelSurface), startY, scoreLabelSurface, screen);
    ApplySurface(GetXScoreBoardItem(scoreValueSurface), startY + textHeight, scoreValueSurface, screen);
    ApplySurface(GetXScoreBoardItem(levelLabelSurface), startY + (textHeight * 2), levelLabelSurface, screen);
    ApplySurface(GetXScoreBoardItem(levelValueSurface), startY + (textHeight * 3), levelValueSurface, screen);

    //
    // Free SDL items.
    //

    TTF_CloseFont(font);
    SDL_FreeSurface(scoreLabelSurface);
    SDL_FreeSurface(levelLabelSurface);
    SDL_FreeSurface(scoreValueSurface);
    SDL_FreeSurface(levelValueSurface);
}

const int LayerControl::GetXScoreBoardItem(const SDL_Surface *surface)
{
    return (PUZZLE_WIDTH + (CONTROL_PADDING_WIDTH)) + (((CONTROL_PADDING_WIDTH) - surface->clip_rect.w)/2);
}

const bool LayerControl::ButtonClicked(const int x, const int y, Button &button)
{
    return ((x > button.GetX() && x < (button.GetX() + CONTROL_BUTTON_WIDTH)) &&
            (y > button.GetX() && y < (button.GetY() + CONTROL_BUTTON_HEIGHT)));
}
