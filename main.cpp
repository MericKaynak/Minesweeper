#include "src/GameRenderer.hpp"
#include <gtkmm.h>

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    Gtk::Window window;
    window.set_title("GTK Renderer Example");
    window.set_default_size(600, 600);

    GameRenderer renderer(window);
    renderer.start();

    return app->run(window);
}
