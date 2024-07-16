#include "Menu.hpp"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <array>


Menu::Menu(SDL_Window* window) : sdlWindow(window) {
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
}

Menu::~Menu() {
    if (sdlRenderer) {
        SDL_DestroyRenderer(sdlRenderer);
    }
}

int Menu::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x = event.button.x;
        int y = event.button.y;

        if (x >= 300 && x <= 500) {
            if (y >= 100 && y <= 150) {
                return 1; // Level 1
            } else if (y >= 200 && y <= 250) {
                return 2; // Level 2
            } else if (y >= 300 && y <= 350) {
                return 3; // Level 3
            } else if (y >= 400 && y <= 450) {
                return 4; // Level 4
            }
        }
    }
    return 0;
}

void Menu::render() const {
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
    SDL_RenderClear(sdlRenderer);

    SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);

    constexpr std::array<std::pair<int, int>, 4> positions = {{
        {300, 100}, {300, 200}, {300, 300}, {300, 400}
    }};

    for (const auto& pos : positions) {
        SDL_Rect rect{ pos.first, pos.second, 200, 50 };
        SDL_RenderFillRect(sdlRenderer, &rect);
    }
}