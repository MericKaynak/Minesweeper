#include "GameRenderer.hpp"
#include <iostream>
#include "style.h"

GameRenderer::GameRenderer(std::shared_ptr<Gtk::Window> win) : window(win), grid(nullptr), revealComplete(false), flagRestartOK(true)
{
  numRows = 0;
  numCols = 0;
  numMines = 0;
  window->signal_key_press_event().connect(sigc::mem_fun(*this, &GameRenderer::on_key_press_event));
  dialog = std::make_unique<Gtk::Dialog>("Select Difficulty", &(*win));

  auto add_button = [this](const std::string &label, int rows, int cols, int bombs)
  {
    Gtk::Button *button = Gtk::manage(new Gtk::Button(label));
    button->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &GameRenderer::level_selected), rows, cols, bombs));
    dialog->get_content_area()->pack_start(*button);
  };

  add_button("Level 1 (8x8 with 8 bombs)", 8, 8, 8);
  add_button("Level 2 (12x12 with 25 bombs)", 12, 12, 25);
  add_button("Level 3 (16x16 with 38 bombs)", 16, 16, 38);
  add_button("Level 4 (22x22 with 90 bombs)", 22, 22, 90);

  dialog->get_content_area()->show_all();
}

void GameRenderer::level_selected(int rows, int cols, int mines)
{
  dialog->hide();
  window->remove();
  numRows = rows;
  numCols = cols;
  numMines = mines;
  buttons.resize(numRows, std::vector<Gtk::Button *>(numCols, nullptr));
  this->startGame();
}

void GameRenderer::start()
{
  dialog->run();
  dialog->hide();
}

// erstellen eines gridlayouts mit buttons
// jeder button entpricht eine spielfeld
void GameRenderer::startGame()
{
  window->set_size_request(cellWidth * numCols, cellHeight * numRows);
  grid = Gtk::manage(new Gtk::Grid());
  grid->set_row_homogeneous(true);
  grid->set_column_homogeneous(true);

  game = std::make_unique<Game>(numRows, numCols, numMines);
  auto css_provider = Gtk::CssProvider::create();
  css_provider->load_from_data("button { font-size: 30px; background: white;}");

  for (int row = 0; row < numRows; row++)
  {
    for (int col = 0; col < numCols; col++)
    {
      Gtk::Button *button = Gtk::manage(new Gtk::Button());
      button->set_size_request(cellWidth, cellHeight);
      grid->attach(*button, col, row, 1, 1);
      buttons[row][col] = button;
      button->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

      button->signal_button_press_event().connect([this, row, col](GdkEventButton *event)
                                                  {
                if (event->button == 3) {
                    on_right_click(row, col);
                } else {
                    on_left_click(row, col);
                }
                return true; });
    }
  }
  window->add(*grid);
  window->show_all();
}

void GameRenderer::restart()
{
  if (!flagRestartOK)
    return;

  for (int row = 0; row < numRows; ++row)
  {
    for (int col = 0; col < numCols; ++col)
    {
      if (buttons[row][col])
      {
        grid->remove(*buttons[row][col]);
      }
    }
  }

  delete grid;
  window->remove();
  buttons.clear();

  start();
}

GameRenderer::~GameRenderer()
{
  delete grid;
}

void GameRenderer::render()
{
  queue_draw();
}

bool GameRenderer::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
  const Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  cellWidth = width / numCols;
  cellHeight = height / numRows;
  window->remove();
  window->add(*grid);
  return true;
}

void GameRenderer::on_size_allocate(Gtk::Allocation &allocation)
{
  Gtk::DrawingArea::on_size_allocate(allocation);
  queue_draw();
}

void GameRenderer::checkNeighbors(int x, int y)
{
  if (x < 0 || x >= game->width || y < 0 || y >= game->height)
    return;
  if (game->reveal_board[x][y])
    return;
  if (game->getFieldValue(x, y) != 0)
    return;

  game->reveal_board[x][y] = true;

  auto css_provider = Gtk::CssProvider::create();
  css_provider->load_from_data("button {background: lightgrey}");
  auto button = get_button(x, y);
  button->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
  button->set_sensitive(false);

  checkNeighbors(x, y - 1);
  checkNeighbors(x, y + 1);
  checkNeighbors(x - 1, y);
  checkNeighbors(x + 1, y);
}

void GameRenderer::style_button(int x, int y)
{
  auto button = get_button(x, y);
  int value = game->getFieldValue(x, y);
  auto css_provider = Gtk::CssProvider::create();
  css_provider->load_from_data("button {background: lightgrey}");

  if (!game->isRevealed(x, y))
  {
    button->set_always_show_image(false);
  }

  button->set_always_show_image(false);

  // 0 bedeutet das keine bombe in der naehe ist zum erleichtern des spiel wir die region aufgedeckt welche auch die bedingung erfuellt
  if (value == 0)
  {
    checkNeighbors(x, y);
  }
  else if (value == Game::IS_A_BOMB)
  {
    // laden eines Bomben images
    // relative path from which the `AdvancedC` game file lies
    // Glib::RefPtr<Gdk::Pixbuf> originalPixbuf = Gdk::Pixbuf::create_from_file("./assets/bomb.png");
    Glib::RefPtr<Gdk::Pixbuf> originalPixbuf = Gdk::Pixbuf::create_from_file("../src/assets/bomb.png");
    int width = cellWidth - 10;
    int height = cellHeight - 10;
    Glib::RefPtr<Gdk::Pixbuf> scaledPixbuf = originalPixbuf->scale_simple(width, height, Gdk::INTERP_BILINEAR);
    if (scaledPixbuf)
    {
      Gtk::Image *image = Gtk::manage(new Gtk::Image(scaledPixbuf));
      game->gameOver = true;
      button->set_image(*image);
      button->set_always_show_image(true);
      button->set_label("");
      button->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
      button->set_sensitive(false);
    }
  }
  else
  {
    // weder Bombe noch leer das heisst bombe in der naehe, jeder wert hat eine andere farbe
    button->set_label(std::to_string(value));
    std::string color = Style::getColor(value);
    css_provider->load_from_data("button { color: " + color + "; background: lightgrey}");
    button->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    button->set_sensitive(false);
  }
  game->reveal_board[x][y] = true;
}

// reveal eines feldes
void GameRenderer::on_left_click(int x, int y)
{
  style_button(x, y);

  if (game->isWon() || game->isGameOver())
  {
    revealComplete = true;
    flagRestartOK = false;

    // reveale alle Felder in einem 30ms intervall, nativer ansatz mit sleep() ist inkompatibel
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &GameRenderer::reveal_next_cell), 30);

    Gtk::Label *status_label = Gtk::manage(new Gtk::Label(game->isWon() ? "You won!" : "Game Over!"));
    std::string status = game->isWon() ? "You won!" : "Game Over!";
    status_label->set_markup("<span font='24' weight='bold'>" + status + "</span>");
    status_label->set_justify(Gtk::JUSTIFY_CENTER);
    status_label->set_valign(Gtk::ALIGN_CENTER);
    status_label->set_halign(Gtk::ALIGN_CENTER);

    Gtk::Label *retry_label = Gtk::manage(new Gtk::Label("Press R for retry"));
    retry_label->set_justify(Gtk::JUSTIFY_CENTER);
    retry_label->set_valign(Gtk::ALIGN_CENTER);
    retry_label->set_halign(Gtk::ALIGN_CENTER);

    Gtk::Box *box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    box->set_valign(Gtk::ALIGN_CENTER);
    box->set_halign(Gtk::ALIGN_CENTER);
    box->pack_start(*status_label, Gtk::PACK_SHRINK);
    box->pack_start(*retry_label, Gtk::PACK_SHRINK);

    Gtk::EventBox *event_box = Gtk::manage(new Gtk::EventBox());
    event_box->add(*box);
    event_box->set_visible_window(false);

    // sorgt dafuer dass erst nach dem alles revealed wurde das Frame mit dem Status ausgegeben wird
    Glib::signal_timeout().connect([this, event_box]() -> bool
                                   {
            if (this->all_cells_revealed()) {
                flagRestartOK = true;
                this->window->remove();
                this->window->add(*event_box);
                this->window->show_all_children();
                return false;
            }
            return true; }, 75);
  }
}

// ermoeglicht felder mit Flaggen zu makieren
void GameRenderer::on_right_click(int x, int y)
{
  if (game->isRevealed(x, y))
    return;
  auto button = get_button(x, y);
  auto css_provider = Gtk::CssProvider::create();

  if (button->get_always_show_image())
  {
    css_provider->load_from_data("button {background: white}");
    button->set_always_show_image(false);
    button->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    return;
  }
  // relative path from which the `AdvancedC` game file lies
  Glib::RefPtr<Gdk::Pixbuf> originalPixbuf = Gdk::Pixbuf::create_from_file("../src/assets/flag.png");
  // Glib::RefPtr<Gdk::Pixbuf> originalPixbuf = Gdk::Pixbuf::create_from_file("./assets/flag.png");
  int width = cellWidth - 10;
  int height = cellHeight - 10;
  Glib::RefPtr<Gdk::Pixbuf> scaledPixbuf = originalPixbuf->scale_simple(width, height, Gdk::INTERP_BILINEAR);

  css_provider->load_from_data("button {background: lightgrey}");
  if (scaledPixbuf)
  {
    Gtk::Image *image = Gtk::manage(new Gtk::Image(scaledPixbuf));
    button->set_image(*image);
    button->set_always_show_image(true);
    button->set_label("");
    button->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
  }
}

Gtk::Button *GameRenderer::get_button(int row, int col)
{
  if (row >= 0 && row < numRows && col >= 0 && col < numCols)
  {
    return buttons[row][col];
  }
  return nullptr;
}

bool GameRenderer::on_key_press_event(GdkEventKey *event)
{
  if (event->keyval == GDK_KEY_r || event->keyval == GDK_KEY_R)
  {
    restart();
    return true;
  }
  if (event->keyval == GDK_KEY_Escape)
  {
    return true;
  }
  return false;
}

bool GameRenderer::reveal_next_cell()
{
  static int current_row = 0;
  static int current_col = 0;

  if (revealComplete)
  {
    if (current_row < numRows)
    {
      style_button(current_row, current_col);
      current_col++;
      if (current_col >= numCols)
      {
        current_col = 0;
        current_row++;
      }
      return true;
    }
    current_row = 0;
    current_col = 0;
    revealComplete = false;
    return false;
  }
  return false;
}

bool GameRenderer::all_cells_revealed()
{
  for (int row = 0; row < numRows; row++)
  {
    for (int col = 0; col < numCols; col++)
    {
      if (!game->isRevealed(row, col))
      {
        return false;
      }
    }
  }
  return true;
}
