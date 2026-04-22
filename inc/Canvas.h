#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/canvas.h>

class Canvas : public bobcat::Canvas_ {

public:
    Canvas(int x, int y, int w, int h);

    void render();
};

#endif
