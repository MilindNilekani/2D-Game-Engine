#ifndef Window_H
#define Window_H

#include <string>
#include<SDL2/SDL.h>
#include"renderer.h"


class Window
{
    Entity *m_eCharacter;
    Entity *m_eBackground;
    Sprite *m_sSpriteComponent;
    Sprite *m_sBackgroundSpriteComponent;
    float xVel=0, yVel=0;

public:
    bool m_bQuit=false;
    SDL_Event m_Event;
    Window();
    void createWindow(int height, int width, std::string name);
    virtual double update(SDL_Window *win);
};

#endif // Window_H