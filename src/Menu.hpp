#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>

class Menu {
public:
    explicit Menu(SDL_Window* window);
    ~Menu();

    int handleEvent(const SDL_Event& event);
    void render() const;

private:
    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
};

#endif
