#include <Application.h>

using namespace bobcat;

namespace {
Button* makeButton(int x, int y, int w, int h, const std::string& label) {
    auto* button = new Button(x, y, w, h, label);
    button->labelsize(12);
    return button;
}
}

Application::Application() {
    window = new Window(1200, 760, "Paint Application");
    window->begin();
    canvas = new Canvas(10, 10, 860, 740);
    int panelX = 885;
    int buttonW = 135;
    int buttonH = 30;
    int rowY = 20;
    int gap = 38;

    objectSelectionText = new TextBox(panelX, rowY-10, 250, 24, "Selected object: none");
    objectSelectionText->labelsize(13);

    toolSelectionText = new TextBox(panelX, rowY+5, 250, 24, "Selected tool: Brush");
    toolSelectionText->labelsize(13);

    const std::vector<std::pair<std::string, Canvas::Tool>> toolDefs = {
        {"Brush", Canvas::Tool::Brush},
        {"Erase", Canvas::Tool::Eraser},
        {"Select", Canvas::Tool::Select},
        {"Rectangle", Canvas::Tool::Rectangle},
        {"Circle", Canvas::Tool::Circle},
        {"Triangle", Canvas::Tool::Triangle},
        {"Pentagon", Canvas::Tool::Pentagon},
        {"Star", Canvas::Tool::Star},
    };

    int toolStartY = rowY + 38;
    for (size_t i = 0; i < toolDefs.size(); ++i) {
        int col = static_cast<int>(i % 2);
        int row = static_cast<int>(i / 2);
        auto* button = makeButton(panelX + col * (buttonW + 10), toolStartY + row * gap, buttonW, buttonH, toolDefs[i].first);
        toolButtons.push_back(button);
        button->onClick([this, toolDefs, i](Widget*) {
            setTool(toolDefs[i].second);
        });
    }

    int actionY = toolStartY + 4 * gap + 10;
    undoButton = makeButton(panelX, actionY, buttonW, buttonH, "Undo");
    redoButton = makeButton(panelX + buttonW + 10, actionY, buttonW, buttonH, "Redo");
    clearButton = makeButton(panelX, actionY + gap, buttonW, buttonH, "Clear");
    frontButton = makeButton(panelX + buttonW + 10, actionY + gap, buttonW, buttonH, "Bring Front");
    backButton = makeButton(panelX, actionY + 2 * gap, buttonW, buttonH, "Send Back");

    undoButton->onClick([this](Widget*) { canvas->undo(); refreshSelectionLabel(); });
    redoButton->onClick([this](Widget*) { canvas->redo(); refreshSelectionLabel(); });
    clearButton->onClick([this](Widget*) { canvas->clearAll(); refreshSelectionLabel(); });
    frontButton->onClick([this](Widget*) { canvas->bringSelectedToFront(); });
    backButton->onClick([this](Widget*) { canvas->sendSelectedToBack(); });

    TextBox* colorLabel = new TextBox(panelX, actionY + 3 * gap + 10, 180, 24, "RGB color picker");
    colorLabel->labelsize(13);

    colorNameText = new TextBox(panelX, actionY + 3 * gap - 7, 180, 24, "Current color: black");
    colorNameText->labelsize(13);

    redSlider = new ColorSlider(panelX, actionY + 3 * gap + 40, 260, 42, "Red", FL_RED);
    greenSlider = new ColorSlider(panelX, actionY + 3 * gap + 78, 260, 42, "Green", FL_GREEN);
    blueSlider = new ColorSlider(panelX, actionY + 3 * gap + 116, 260, 42, "Blue", FL_BLUE);

    redSlider->value(0);
    greenSlider->value(0);
    blueSlider->value(0);

    colorPreview = new TextBox(panelX + 130, actionY + 3 * gap + 10, 130, 22, "");
    colorPreview->box(FL_FLAT_BOX);
    colorPreview->color(FL_BLACK);
    
    canvas->onMouseDown([this](Widget*, float x, float y) {
        canvas->mouseDown(nullptr, x, y);
        refreshSelectionLabel();
    });
    canvas->onDrag([this](Widget*, float x, float y) {
        canvas->mouseDrag(nullptr, x, y);
        refreshSelectionLabel();
    });
    canvas->onMouseUp([this](Widget*, float x, float y) {
        canvas->mouseUp(nullptr, x, y);
        refreshSelectionLabel();
    });

    auto colorChanged = [this](Widget*) { syncColorFromSliders(); };
    redSlider->onChange(colorChanged);
    greenSlider->onChange(colorChanged);
    blueSlider->onChange(colorChanged);

    canvas->setTool(Canvas::Tool::Brush);
    canvas->setCurrentColor(0, 0, 0, false);
    refreshSelectionLabel();
    window->end();
    window->resizable(canvas);
    window->size_range(750, 600);
    window->show();
}

void Application::refreshSelectionLabel() {
    if (canvas->hasSelection() && canvas->selectedShape()) {
        auto c = canvas->selectedShape()->color();
        redSlider->value(static_cast<int>(c.r * 255.0f));
        greenSlider->value(static_cast<int>(c.g * 255.0f));
        blueSlider->value(static_cast<int>(c.b * 255.0f));
        objectSelectionText->label("Selected object: " + getColorName(canvas->selectedShape()->color().r * 255, canvas->selectedShape()->color().g * 255, canvas->selectedShape()->color().b * 255) + " " + canvas->selectedShape()->type());
    } else {
        objectSelectionText->label("Selected object: none");
    }
}
void Application::syncColorFromSliders() {
    canvas->setCurrentColor(redSlider->value(), greenSlider->value(), blueSlider->value(), true);
    colorPreview->color(fl_rgb_color(redSlider->value(), greenSlider->value(), blueSlider->value()));
    colorPreview->redraw();
    refreshSelectionLabel();
    colorNameText->label("Current color: " + getColorName(redSlider->value(), greenSlider->value(), blueSlider->value()));
}

void Application::setTool(Canvas::Tool tool) {
    canvas->setTool(tool);
    refreshSelectionLabel();
    setToolText(static_cast<int>(tool));
}

void Application::setToolText(int tool) {
    switch(tool) {
        case 0:
            toolSelectionText->label("Selected tool: Brush");
            break;
        case 1:
            toolSelectionText->label("Selected tool: Eraser");
            break;
        case 2:
            toolSelectionText->label("Selected tool: Select");
            break;
        case 3:
            toolSelectionText->label("Selected tool: Rectangle");
            break;
        case 4:
            toolSelectionText->label("Selected tool: Circle");
            break;
        case 5:
            toolSelectionText->label("Selected tool: Triangle");
            break;
        case 6:
            toolSelectionText->label("Selected tool: Pentagon");
            break;
        case 7:
            toolSelectionText->label("Selected tool: Star");
            break;
        default:
            toolSelectionText->label("Selected tool: none");
            break;
    }
}
