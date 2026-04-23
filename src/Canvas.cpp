#include <Canvas.h>

#include <OpenGL/gl.h>

using namespace std;

namespace {
constexpr float PI = 3.14159265358979323846f;

float clampf(float v, float lo, float hi) {
    return std::max(lo, std::min(v, hi));
}

void drawPolyline(const std::vector<Canvas::Point>& pts, int w, int h, bool closed = false) {
    if (pts.empty()) return;
    glBegin(closed ? GL_LINE_LOOP : GL_LINE_STRIP);
    for (const auto& p : pts) {
        glVertex2f((2.0f * p.x / w) - 1.0f, 1.0f - (2.0f * p.y / h));
    }
    glEnd();
}

std::vector<Canvas::Point> polygonVertices(Canvas::Point center, float radius, int sides, bool star) {
    std::vector<Canvas::Point> pts;
    sides = std::max(3, sides);
    if (!star) {
        for (int i = 0; i < sides; ++i) {
            float angle = (-PI / 2.0f) + (2.0f * PI * i / sides);
            pts.push_back(Canvas::Point{center.x + radius * std::cos(angle), center.y + radius * std::sin(angle)});
        }
    } else {
        float inner = radius * 0.45f;
        int total = sides * 2;
        for (int i = 0; i < total; ++i) {
            float rr = (i % 2 == 0) ? radius : inner;
            float angle = (-PI / 2.0f) + (2.0f * PI * i / total);
            pts.push_back(Canvas::Point{center.x + rr * std::cos(angle), center.y + rr * std::sin(angle)});
        }
    }
    return pts;
}
}

Canvas::ScribbleShape::ScribbleShape(Color c, Point start) {
    color(c);
    points_.push_back(start);
}

void Canvas::ScribbleShape::addPoint(Point p) { points_.push_back(p); }

void Canvas::ScribbleShape::draw(int w, int h) const {
    auto c = color();
    glColor3f(c.r, c.g, c.b);
    glLineWidth(3.0f);
    drawPolyline(points_, w, h, false);
    glPointSize(4.0f);
    glBegin(GL_POINTS);
    for (const auto& p : points_) {
        glVertex2f((2.0f * p.x / w) - 1.0f, 1.0f - (2.0f * p.y / h));
    }
    glEnd();
}

bool Canvas::ScribbleShape::hitTest(Point p) const {
    if (points_.empty()) return false;
    auto bb = bounds();
    if (p.x < bb.first.x - 8 || p.x > bb.second.x + 8 || p.y < bb.first.y - 8 || p.y > bb.second.y + 8) return false;
    if (points_.size() == 1) return dist(points_[0], p) <= 8.0f;
    for (size_t i = 1; i < points_.size(); ++i) {
        if (distanceToSegment(p, points_[i - 1], points_[i]) <= 7.0f) return true;
    }
    return false;
}

void Canvas::ScribbleShape::move(float dx, float dy) {
    for (auto& pt : points_) {
        pt.x += dx;
        pt.y += dy;
    }
}

void Canvas::ScribbleShape::resizeFromBox(Point a, Point b) {
    auto bb = bounds();
    float oldW = bb.second.x - bb.first.x;
    float oldH = bb.second.y - bb.first.y;
    float newW = b.x - a.x;
    float newH = b.y - a.y;
    if (std::fabs(oldW) < 0.001f || std::fabs(oldH) < 0.001f) return;
    for (auto& pt : points_) {
        float nx = (pt.x - bb.first.x) / oldW;
        float ny = (pt.y - bb.first.y) / oldH;
        pt.x = a.x + nx * newW;
        pt.y = a.y + ny * newH;
    }
}

std::pair<Canvas::Point, Canvas::Point> Canvas::ScribbleShape::bounds() const {
    Point lo{points_.empty() ? 0.0f : points_[0].x, points_.empty() ? 0.0f : points_[0].y};
    Point hi = lo;
    for (const auto& p : points_) {
        lo.x = std::min(lo.x, p.x);
        lo.y = std::min(lo.y, p.y);
        hi.x = std::max(hi.x, p.x);
        hi.y = std::max(hi.y, p.y);
    }
    if (std::fabs(hi.x - lo.x) < 1.0f) { hi.x = lo.x + 1.0f; }
    if (std::fabs(hi.y - lo.y) < 1.0f) { hi.y = lo.y + 1.0f; }
    return {lo, hi};
}

Canvas::RectShape::RectShape(Color c, Point a, Point b) {
    color(c);
    a_ = a;
    b_ = b;
}

void Canvas::RectShape::setPoints(Point a, Point b) { a_ = a; b_ = b; }

void Canvas::RectShape::draw(int w, int h) const {
    auto bb = bounds();
    auto c = color();
    glColor3f(c.r, c.g, c.b);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f((2.0f * bb.first.x / w) - 1.0f, 1.0f - (2.0f * bb.first.y / h));
    glVertex2f((2.0f * bb.second.x / w) - 1.0f, 1.0f - (2.0f * bb.first.y / h));
    glVertex2f((2.0f * bb.second.x / w) - 1.0f, 1.0f - (2.0f * bb.second.y / h));
    glVertex2f((2.0f * bb.first.x / w) - 1.0f, 1.0f - (2.0f * bb.second.y / h));
    glEnd();
}

bool Canvas::RectShape::hitTest(Point p) const {
    auto bb = bounds();
    return p.x >= bb.first.x && p.x <= bb.second.x && p.y >= bb.first.y && p.y <= bb.second.y;
}

void Canvas::RectShape::move(float dx, float dy) { a_.x += dx; a_.y += dy; b_.x += dx; b_.y += dy; }

void Canvas::RectShape::resizeFromBox(Point a, Point b) { a_ = a; b_ = b; }

std::pair<Canvas::Point, Canvas::Point> Canvas::RectShape::bounds() const {
    Point lo{std::min(a_.x, b_.x), std::min(a_.y, b_.y)};
    Point hi{std::max(a_.x, b_.x), std::max(a_.y, b_.y)};
    return {lo, hi};
}

Canvas::CircleShape::CircleShape(Color c, Point a, Point b) {
    color(c);
    setPoints(a, b);
}

void Canvas::CircleShape::setPoints(Point a, Point b) {
    center_ = Point{(a.x + b.x) / 2.0f, (a.y + b.y) / 2.0f};
    radius_ = std::max(std::fabs(b.x - a.x), std::fabs(b.y - a.y)) / 2.0f;
    if (radius_ < 1.0f) radius_ = 1.0f;
}

void Canvas::CircleShape::draw(int w, int h) const {
    auto c = color();
    glColor3f(c.r, c.g, c.b);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    const int segments = 48;
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        float px = center_.x + radius_ * std::cos(angle);
        float py = center_.y + radius_ * std::sin(angle);
        glVertex2f((2.0f * px / w) - 1.0f, 1.0f - (2.0f * py / h));
    }
    glEnd();
}

bool Canvas::CircleShape::hitTest(Point p) const {
    return dist(center_, p) <= radius_;
}

void Canvas::CircleShape::move(float dx, float dy) { center_.x += dx; center_.y += dy; }

void Canvas::CircleShape::resizeFromBox(Point a, Point b) { setPoints(a, b); }

std::pair<Canvas::Point, Canvas::Point> Canvas::CircleShape::bounds() const {
    return {Point{center_.x - radius_, center_.y - radius_}, Point{center_.x + radius_, center_.y + radius_}};
}

Canvas::PolygonShape::PolygonShape(Color c, Point a, Point b, int sides, bool star) : sides_(sides), star_(star) {
    color(c);
    setPoints(a, b);
}

void Canvas::PolygonShape::setPoints(Point a, Point b) {
    center_ = Point{(a.x + b.x) / 2.0f, (a.y + b.y) / 2.0f};
    radius_ = std::max(std::fabs(b.x - a.x), std::fabs(b.y - a.y)) / 2.0f;
    if (radius_ < 1.0f) radius_ = 1.0f;
}

void Canvas::PolygonShape::draw(int w, int h) const {
    auto c = color();
    glColor3f(c.r, c.g, c.b);
    glLineWidth(3.0f);
    auto pts = polygonVertices(center_, radius_, sides_, star_);
    drawPolyline(pts, w, h, true);
}

bool Canvas::PolygonShape::hitTest(Point p) const {
    return pointInPolygon(p, polygonVertices(center_, radius_, sides_, star_));
}

void Canvas::PolygonShape::move(float dx, float dy) { center_.x += dx; center_.y += dy; }

void Canvas::PolygonShape::resizeFromBox(Point a, Point b) { setPoints(a, b); }

std::pair<Canvas::Point, Canvas::Point> Canvas::PolygonShape::bounds() const {
    return {Point{center_.x - radius_, center_.y - radius_}, Point{center_.x + radius_, center_.y + radius_}};
}

Canvas::Canvas(int x, int y, int w, int h) : bobcat::Canvas_(x, y, w, h) {
    currentColor_ = Color{0.0f, 0.0f, 0.0f};
}

Canvas::Point Canvas::toPixels(float nx, float ny) const {
    return Point{(nx + 1.0f) * 0.5f * static_cast<float>(w()), (1.0f - ny) * 0.5f * static_cast<float>(h())};
}

float Canvas::toGLX(float px) const { return (2.0f * px / static_cast<float>(w())) - 1.0f; }
float Canvas::toGLY(float py) const { return 1.0f - (2.0f * py / static_cast<float>(h())); }

void Canvas::clearSelection() { selected_.reset(); }

void Canvas::setSelection(const std::shared_ptr<Shape>& s) { selected_ = s; }

std::shared_ptr<Canvas::Shape> Canvas::hitTestTopmost(Point p) const {
    for (auto it = shapes_.rbegin(); it != shapes_.rend(); ++it) {
        if ((*it)->hitTest(p)) return *it;
    }
    return nullptr;
}

void Canvas::pushShape(const std::shared_ptr<Shape>& s) {
    shapes_.push_back(s);
    redo_.clear();
    redraw();
}

void Canvas::commitDraft() {
    if (!draft_) return;
    shapes_.push_back(draft_);
    redo_.clear();
    draft_.reset();
    redraw();
}

std::pair<Canvas::Point, Canvas::Point> Canvas::currentBounds() const {
    return selected_ ? selected_->bounds() : std::make_pair(Point{0, 0}, Point{0, 0});
}

bool Canvas::nearHandle(Point p) const {
    if (!selected_) return false;
    auto bb = selected_->bounds();
    return std::fabs(p.x - bb.second.x) <= HANDLE_SIZE && std::fabs(p.y - bb.second.y) <= HANDLE_SIZE;
}

void Canvas::render() {
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);

    for (const auto& shape : shapes_) {
        shape->draw(w(), h());
    }
    if (draft_) {
        draft_->draw(w(), h());
    }

    if (selected_) {
        auto bb = selected_->bounds();
        glColor3f(1.0f, 0.85f, 0.0f);
        glLineWidth(1.5f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(toGLX(bb.first.x), toGLY(bb.first.y));
        glVertex2f(toGLX(bb.second.x), toGLY(bb.first.y));
        glVertex2f(toGLX(bb.second.x), toGLY(bb.second.y));
        glVertex2f(toGLX(bb.first.x), toGLY(bb.second.y));
        glEnd();

        glColor3f(1.0f, 0.85f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(toGLX(bb.second.x - 5), toGLY(bb.second.y - 5));
        glVertex2f(toGLX(bb.second.x + 5), toGLY(bb.second.y - 5));
        glVertex2f(toGLX(bb.second.x + 5), toGLY(bb.second.y + 5));
        glVertex2f(toGLX(bb.second.x - 5), toGLY(bb.second.y + 5));
        glEnd();
    }
}

void Canvas::setTool(Tool tool) {
    tool_ = tool;
    moving_ = false;
    resizing_ = false;
    draft_.reset();
    redraw();
}

void Canvas::setCurrentColor(int r, int g, int b, bool applyToSelection) {
    currentColor_ = Color{r / 255.0f, g / 255.0f, b / 255.0f};
    if (applyToSelection && selected_) {
        selected_->color(currentColor_);
    }
    redraw();
}

void Canvas::selectAt(Point p) {
    auto hit = hitTestTopmost(p);
    setSelection(hit);
    moving_ = false;
    resizing_ = false;
    redraw();
}

void Canvas::eraseAt(Point p) {
    for (auto it = shapes_.rbegin(); it != shapes_.rend(); ++it) {
        if ((*it)->hitTest(p)) {
            if (selected_ == *it) clearSelection();
            shapes_.erase(std::next(it).base());
            redraw();
            return;
        }
    }
}

void Canvas::mouseDown(bobcat::Widget*, float nx, float ny) {
    Point p = toPixels(nx, ny);
    mouseDown_ = p;
    dragStart_ = p;

    switch (tool_) {
        case Tool::Brush:
            draft_ = make_shared<ScribbleShape>(currentColor_, p);
            break;
        case Tool::Rectangle:
            draft_ = make_shared<RectShape>(currentColor_, p, p);
            break;
        case Tool::Circle:
            draft_ = make_shared<CircleShape>(currentColor_, p, p);
            break;
        case Tool::Triangle:
            draft_ = make_shared<PolygonShape>(currentColor_, p, p, 3, false);
            break;
        case Tool::Pentagon:
            draft_ = make_shared<PolygonShape>(currentColor_, p, p, 5, false);
            break;
        case Tool::Star:
            draft_ = make_shared<PolygonShape>(currentColor_, p, p, 5, true);
            break;
        case Tool::Eraser:
            eraseAt(p);
            break;
        case Tool::Select:
            if (selected_ && nearHandle(p)) {
                resizing_ = true;
                resizeAnchor_ = selected_->bounds().first;
                moving_ = false;
            } else {
                auto hit = hitTestTopmost(p);
                setSelection(hit);
                if (selected_) {
                    auto bb = selected_->bounds();
                    if (selected_->hitTest(p)) {
                        moving_ = true;
                        dragStart_ = p;
                    }
                }
            }
            redraw();
            break;
    }
}

void Canvas::mouseDrag(bobcat::Widget*, float nx, float ny) {
    Point p = toPixels(nx, ny);

    if (draft_) {
        if (auto scribble = dynamic_pointer_cast<ScribbleShape>(draft_)) {
            scribble->addPoint(p);
        } else {
            draft_->resizeFromBox(mouseDown_, p);
        }
        redraw();
        return;
    }

    if (tool_ == Tool::Select && selected_) {
        if (resizing_) {
            selected_->resizeFromBox(resizeAnchor_, p);
            redraw();
            return;
        }
        if (moving_) {
            float dx = p.x - dragStart_.x;
            float dy = p.y - dragStart_.y;
            selected_->move(dx, dy);
            dragStart_ = p;
            redraw();
            return;
        }
    }

    if (tool_ == Tool::Eraser) {
        eraseAt(p);
    }
}

void Canvas::mouseUp(bobcat::Widget*, float nx, float ny) {
    Point p = toPixels(nx, ny);
    if (draft_) {
        if (auto scribble = dynamic_pointer_cast<ScribbleShape>(draft_)) {
            scribble->addPoint(p);
        } else {
            draft_->resizeFromBox(mouseDown_, p);
        }
        commitDraft();
    }
    moving_ = false;
    resizing_ = false;
}

void Canvas::undo() {
    if (shapes_.empty()) return;
    redo_.push_back(shapes_.back());
    if (selected_ == shapes_.back()) clearSelection();
    shapes_.pop_back();
    redraw();
}

void Canvas::redo() {
    if (redo_.empty()) return;
    shapes_.push_back(redo_.back());
    redo_.pop_back();
    redraw();
}

void Canvas::clearAll() {
    shapes_.clear();
    redo_.clear();
    draft_.reset();
    clearSelection();
    redraw();
}

void Canvas::bringSelectedToFront() {
    if (!selected_) return;
    auto it = std::find(shapes_.begin(), shapes_.end(), selected_);
    if (it == shapes_.end()) return;
    auto obj = *it;
    shapes_.erase(it);
    shapes_.push_back(obj);
    redraw();
}

void Canvas::sendSelectedToBack() {
    if (!selected_) return;
    auto it = std::find(shapes_.begin(), shapes_.end(), selected_);
    if (it == shapes_.end()) return;
    auto obj = *it;
    shapes_.erase(it);
    shapes_.insert(shapes_.begin(), obj);
    redraw();
}
