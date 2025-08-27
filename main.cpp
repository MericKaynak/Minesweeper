#include "src/GameRenderer.hpp"
#include <gtkmm.h>

int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  std::shared_ptr<Gtk::Window> window = std::make_shared<Gtk::Window>();
  window->set_title("Minesweeper");
  window->set_default_size(600, 600);

  GameRenderer game(window);
  game.start();

  return app->run(*window);
}
