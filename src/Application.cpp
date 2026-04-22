#include <Application.h>

using namespace bobcat;

Application::Application() {
    window = new Window(25, 75, 400, 400, "Pain Application");

    canvas = new Canvas(0, 0, 400, 400);

    window->show();
}
