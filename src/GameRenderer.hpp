#ifndef GAMERENDERER_HPP
#define GAMERENDERER_HPP

#include <gtkmm.h>
#include <string>
#include <vector>
#include "Game.hpp"
#include "style.h"

class GameRenderer : public Gtk::DrawingArea {
public:
    GameRenderer(Gtk::Window& window);
    virtual ~GameRenderer();

    void render();
    Gtk::Button* get_button(int row, int col);
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    void on_size_allocate(Gtk::Allocation& allocation) override;
    void start();
    void restart();

private:
    void style_button(int x, int y);
    void firstTryFill(int x, int y);
    bool on_key_press_event(GdkEventKey* event) override;
    void on_cell_clicked(int x, int y);
    void update_visibility(); // Neue Methode für die Sichtbarkeit der Game Over Nachrichten
    void show_game_over();    // Methode zum Anzeigen des Game Over Overlays
    void hide_game_over();    // Methode zum Verstecken des Game Over Overlays
    Game* game;
    Gtk::Window& window;
    Gtk::Grid* grid;
    const int numRows = 10;
    const int numCols = 10;
    int cellWidth = 50;
    int cellHeight = 50;
    bool firstTry = true;
    std::vector<std::vector<Gtk::Button*>> buttons;
};

#endif // GAMERENDERER_HPP
