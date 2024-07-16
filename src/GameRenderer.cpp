#include "GameRenderer.hpp"
#include <iostream>

GameRenderer::GameRenderer(Gtk::Window& win) : window(win), buttons(numRows, std::vector<Gtk::Button*>(numCols, nullptr)), grid(nullptr) {
    window.signal_key_press_event().connect(sigc::mem_fun(*this, &GameRenderer::on_key_press_event));
}

void GameRenderer::start() {
    window.set_size_request(500, 500);
    firstTry=true;

    grid = Gtk::manage(new Gtk::Grid());
    grid->set_row_homogeneous(true);
    grid->set_column_homogeneous(true);

    game = new Game(numRows,numCols,10);
    auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data("button { font-size: 30px; background: white}");

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            Gtk::Button* button = Gtk::manage(new Gtk::Button());
            button->set_size_request(cellWidth, cellHeight);
            grid->attach(*button, col, row, 1, 1);
            buttons[row][col] = button;
            button->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

            button->signal_button_press_event().connect([this, row, col](GdkEventButton* event) {
                if (event->button == 3) {
                    on_right_click(row, col);
                }   else {
                   on_left_click(row, col);
               }
             return true;
             });
        }
    }
    window.add(*grid);
    window.show_all();
}

void GameRenderer::restart() {
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (buttons[row][col]) {
                grid->remove(*buttons[row][col]);
            }
        }
    }
    buttons.clear();
    buttons.resize(numRows, std::vector<Gtk::Button*>(numCols, nullptr));

    window.remove();


    start();
}

GameRenderer::~GameRenderer() {}

void GameRenderer::render() {
    queue_draw();
}

bool GameRenderer::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    cellWidth = width / numCols;
    cellHeight = height/ numRows;
    return true;
}

void GameRenderer::on_size_allocate(Gtk::Allocation& allocation) {
    Gtk::DrawingArea::on_size_allocate(allocation);
    queue_draw();
}

void GameRenderer::firstTryFill(int startX, int startY) {

    // Ein einfache rekursive Funktion hat zum stackoverflow gefuehrt deswegen der komplexe ansatz

    if (startX < 0 || startX >= game->width || startY < 0 || startY >= game->height) return;

    std::stack<std::pair<int, int>> stack;
    std::vector<std::pair<int, int>> positions_to_update;

    stack.push({startX, startY});

    while (!stack.empty()) {
        auto [x, y] = stack.top();
        stack.pop();

        if (x < 0 || x >= game->width || y < 0 || y >= game->height) continue;
        if (game->reveal_board[x][y] == true) continue;

        int value = game->reveal(x, y);
        if (value != 0) continue;

        game->reveal_board[x][y] = true;

        positions_to_update.push_back({x, y});


        stack.push({x + 1, y});
        stack.push({x, y + 1});
        stack.push({x - 1, y});
        stack.push({x, y - 1});
    }

    auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data("button {background: lightgrey}");

    for (const auto& pos : positions_to_update) {
        int x = pos.first;
        int y = pos.second;
        auto button = get_button(y, x);
        button->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
        button->set_sensitive(false);
    }
}

void GameRenderer::style_button(int x, int y) {
    auto button = get_button(x, y);
    int value=game->reveal(x,y);
    auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data("button {background: lightgrey}");

    if (!game->isRevealed(x,y)) {
        button->set_always_show_image(false);
    }


    if (value==0 and firstTry) {
        firstTryFill(x,y);
    }
    else if (value==0) {
        button->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
        button->set_sensitive(false);

    } else if(value==game->IS_BOMB) {
        game->gameOver=true;
        Glib::RefPtr<Gdk::Pixbuf> originalPixbuf = Gdk::Pixbuf::create_from_file("/mnt/c/Users/meric/CLionProjects/AdvancedCPP/src/assets/bomb.png");
        int width = cellWidth-10;
        int height = cellHeight-10;
        Glib::RefPtr<Gdk::Pixbuf> scaledPixbuf = originalPixbuf->scale_simple(width, height, Gdk::INTERP_BILINEAR);

        if (scaledPixbuf) {
            Gtk::Image* image = Gtk::manage(new Gtk::Image(scaledPixbuf));
            button->set_image(*image);
            button->set_always_show_image(true);
            button->set_label("");
            button->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
            button->set_sensitive(false);
        }
    } else {
        button->set_label(std::to_string(value));
        std::string color=Style::getColor(value);
        css_provider->load_from_data("button { color: "+color+"; font-size: 30px; background: lightgrey}");
        button->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
        button->set_sensitive(false);
    }
    firstTry=false;
}


void GameRenderer::on_left_click(int x, int y) {
    style_button(x,y);
    if (game->isGameOver()) {
        for (int row=0;row<game->height;row++) {
            for (int col=0;col<game->width;col++) {
                style_button(row,col);
            }
        }
    }
}

void GameRenderer::on_right_click(int x, int y) {
    if (game->isRevealed(x,y)) return;
    auto button=get_button(x,y);
    auto css_provider = Gtk::CssProvider::create();

    if (button->get_image()) {
        css_provider->load_from_data("button {background: white}");
        button->set_always_show_image(false);
        button->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
        return;
    }


    Glib::RefPtr<Gdk::Pixbuf> originalPixbuf = Gdk::Pixbuf::create_from_file("/mnt/c/Users/meric/CLionProjects/AdvancedCPP/src/assets/flag.png");
    int width = cellWidth-10;
    int height = cellHeight-10;
    Glib::RefPtr<Gdk::Pixbuf> scaledPixbuf = originalPixbuf->scale_simple(width, height, Gdk::INTERP_BILINEAR);

    css_provider->load_from_data("button {background: lightgrey}");
    if (scaledPixbuf) {
        Gtk::Image* image = Gtk::manage(new Gtk::Image(scaledPixbuf));
        button->set_image(*image);
        button->set_always_show_image(true);
        button->set_label("");
        button->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
}

Gtk::Button* GameRenderer::get_button(int row, int col) {
    if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
        return buttons[row][col];
    }
    return nullptr;
}

bool GameRenderer::on_key_press_event(GdkEventKey* event) {
    if (event->keyval == GDK_KEY_r || event->keyval == GDK_KEY_R) {
        restart();
        return true;
    }
    return false;
}
