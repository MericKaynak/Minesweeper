#ifndef GAMERENDERER_HPP
#define GAMERENDERER_HPP

#include <gtkmm.h>
#include <vector>
#include "Game.hpp"
#include <array>

class GameRenderer : public Gtk::DrawingArea {
public:
    GameRenderer(Gtk::Window& window);
    virtual ~GameRenderer();

    void render();
    Gtk::Button* get_button(int row, int col);
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    void on_size_allocate(Gtk::Allocation& allocation) override;
    void restart();
    void start();

private:
    void style_button(int x, int y);
    void checkNeighbors(int x, int y);
    bool on_key_press_event(GdkEventKey* event) override;
    void on_left_click(int x, int y);
    void on_right_click(int x, int y);
    void update_visibility();
    void show_game_over();
    void hide_game_over();
    void level_selected(int rows, int cols, int mines);
    void startGame();

   [[nodiscard]] bool reveal_next_cell();
   [[nodiscard]] bool all_cells_revealed();

    Gtk::Dialog* dialog;
    Game* game{};
    Gtk::Window& window;
    Gtk::Grid* grid;
    int numRows{};
    int numCols{};
    int numMines{};
    int cellWidth = 40;
    int cellHeight = 40;
    std::vector<std::vector<Gtk::Button*>> buttons;
    bool revealComplete = false;
    bool flagRestartOK=true;
};

#endif // GAMERENDERER_HPP
