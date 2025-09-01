#include "Spritesheet.h"
#include "Log.h"

namespace Tetris {
    Spritesheet::Spritesheet(const char *path, const int row, const int column)
    {
        m_spritesheet_image = SDL_LoadBMP(path);

        if(m_spritesheet_image == nullptr) {
            TETRIS_ERROR("Failed to load image: {}", SDL_GetError());
            return;
        }

        m_clip.w = m_spritesheet_image->w / column;
        m_clip.h = m_spritesheet_image->h / row;
    }

    Spritesheet::~Spritesheet()
    {
        SDL_FreeSurface(m_spritesheet_image);
    }

    void Spritesheet::select_sprite(const int x, const int y)
    {
        m_clip.x = x * m_clip.w;
        m_clip.y = y * m_clip.h;
    }

    void Spritesheet::draw_selected_sprite(SDL_Surface *window_surface, SDL_Rect *position)
    {
        SDL_BlitSurface(m_spritesheet_image, &m_clip, window_surface, position);
    }
}