#include <Canvas.h>
#include <GL/freeglut.h>

Canvas::Canvas(int x, int y, int w, int h) : bobcat::Canvas_(x, y, w, h) {
    //
}

void Canvas::render() {
    glPointSize(15);
    glColor3f(1, 0, 0);

    glBegin(GL_POINTS);
        glVertex2f(0.0, 0.0);
    glEnd();
}
