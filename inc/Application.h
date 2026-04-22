#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>
#include <Canvas.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    Canvas* canvas;

public:
    Application();
};

#endif


