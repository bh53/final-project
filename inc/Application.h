#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>
#include <Canvas.h>
#include <Slider.h>

#include <vector>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    Canvas* canvas;

    std::vector<bobcat::Button*> toolButtons;
    bobcat::Button* undoButton;
    bobcat::Button* redoButton;
    bobcat::Button* clearButton;
    bobcat::Button* frontButton;
    bobcat::Button* backButton;
    ColorSlider* redSlider;
    ColorSlider* greenSlider;
    ColorSlider* blueSlider;
    bobcat::TextBox* objectSelectionText;
    bobcat::TextBox* toolSelectionText;
    bobcat::TextBox* colorPreview;

    void refreshSelectionLabel();
    void syncColorFromSliders();
    void setTool(Canvas::Tool tool);
    void setToolText(int tool);

public:
    Application();

    friend struct ::AppTest;
};

#endif
