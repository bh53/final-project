#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/canvas.h>
#include <FL/gl.h>

#include <algorithm>
#include <cmath>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Canvas : public bobcat::Canvas_ {
public:
    enum class Tool { Brush, Eraser, Select, Rectangle, Circle, Triangle, Pentagon, Star };

    struct Color {
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
    };

    struct Point {
        float x = 0.0f;
        float y = 0.0f;
    };

    class Shape {
        Color color_;

    protected:
        static float dist(Point a, Point b) {
            float dx = a.x - b.x;
            float dy = a.y - b.y;
            return std::sqrt(dx * dx + dy * dy);
        }

        static Point midpoint(Point a, Point b) {
            return Point{(a.x + b.x) / 2.0f, (a.y + b.y) / 2.0f};
        }

        static float clampf(float v, float lo, float hi) {
            return std::max(lo, std::min(v, hi));
        }

            static bool pointInPolygon(Point p, const std::vector<Point>& poly) {
            bool inside = false;
            if (poly.empty()) return false;
            for (size_t i = 0, j = poly.size() - 1; i < poly.size(); j = i++) {
                const Point& a = poly[i];
                const Point& b = poly[j];
                bool intersect = ((a.y > p.y) != (b.y > p.y)) &&
                                 (p.x < (b.x - a.x) * (p.y - a.y) / ((b.y - a.y) == 0.0f ? 0.00001f : (b.y - a.y)) + a.x);
                if (intersect) inside = !inside;
            }
            return inside;
        }

        static float distanceToSegment(Point p, Point a, Point b) {
            float vx = b.x - a.x;
            float vy = b.y - a.y;
            float wx = p.x - a.x;
            float wy = p.y - a.y;
            float c1 = vx * wx + vy * wy;
            if (c1 <= 0) return dist(p, a);
            float c2 = vx * vx + vy * vy;
            if (c2 <= c1) return dist(p, b);
            float t = c1 / c2;
            Point proj{a.x + t * vx, a.y + t * vy};
            return dist(p, proj);
        }

        void applyColor(const Color& c) { color_ = c; }

    public:
        virtual ~Shape() = default;
	virtual std::string type() const = 0;
        Color color() const { return color_; }
        void color(Color c) { color_ = c; }
        virtual void draw(int w, int h) const = 0;
        virtual bool hitTest(Point p) const = 0;
        virtual void move(float dx, float dy) = 0;
        virtual void resizeFromBox(Point a, Point b) = 0;
        virtual std::pair<Point, Point> bounds() const = 0;
    };

    class ScribbleShape : public Shape {
        std::vector<Point> points_;

    public:
        ScribbleShape(Color c, Point start);
        void addPoint(Point p);
        void draw(int w, int h) const override;
        bool hitTest(Point p) const override;
        void move(float dx, float dy) override;
        void resizeFromBox(Point a, Point b) override;
        std::pair<Point, Point> bounds() const override;
	std::string type() const override { return "scribble"; }
    };

    class RectShape : public Shape {
        Point a_;
        Point b_;

    public:
        RectShape(Color c, Point a, Point b);
        void setPoints(Point a, Point b);
        void draw(int w, int h) const override;
        bool hitTest(Point p) const override;
        void move(float dx, float dy) override;
        void resizeFromBox(Point a, Point b) override;
        std::pair<Point, Point> bounds() const override;
	std::string type() const override { return "rectangle"; }
    };

    class CircleShape : public Shape {
        Point center_;
        float radius_;

    public:
        CircleShape(Color c, Point a, Point b);
        void setPoints(Point a, Point b);
        void draw(int w, int h) const override;
        bool hitTest(Point p) const override;
        void move(float dx, float dy) override;
        void resizeFromBox(Point a, Point b) override;
        std::pair<Point, Point> bounds() const override;
	std::string type() const override { return "circle"; }
    };

    class PolygonShape : public Shape {
        Point center_;
        float radius_;
        int sides_;
        bool star_;

    public:
        PolygonShape(Color c, Point a, Point b, int sides, bool star = false);
        void setPoints(Point a, Point b);
        void draw(int w, int h) const override;
        bool hitTest(Point p) const override;
        void move(float dx, float dy) override;
        void resizeFromBox(Point a, Point b) override;
        std::pair<Point, Point> bounds() const override;
	std::string type() const override {
		if (this->star_) { return "Star"; }
		else {
			switch(this->sides_) {
				case 3:
					return "triangle";
					break;
				case 5:
					return "pentagon";
					break;
				default:
					return "polygon";
			}

		}
	}
    };

private:
    std::vector<std::shared_ptr<Shape>> shapes_;
    std::vector<std::shared_ptr<Shape>> redo_;
    std::shared_ptr<Shape> draft_;
    std::shared_ptr<Shape> selected_;
    Tool tool_ = Tool::Brush;
    Color currentColor_;
    Point mouseDown_{};
    Point dragStart_{};
    Point resizeAnchor_{};
    bool moving_ = false;
    bool resizing_ = false;
    bool suppressHistory_ = false;

    static constexpr float HANDLE_SIZE = 10.0f;

    Point toPixels(float nx, float ny) const;
    float toGLX(float px) const;
    float toGLY(float py) const;
    std::pair<Point, Point> currentBounds() const;
    bool nearHandle(Point p) const;
    void clearSelection();
    void setSelection(const std::shared_ptr<Shape>& s);
    std::shared_ptr<Shape> hitTestTopmost(Point p) const;
    void commitDraft();
    void pushShape(const std::shared_ptr<Shape>& s);

public:
    Canvas(int x, int y, int w, int h);

    void render() override;
    void setTool(Tool tool);
    Tool tool() const { return tool_; }
    void setCurrentColor(int r, int g, int b, bool applyToSelection = true);
    Color currentColor() const { return currentColor_; }
    void selectAt(Point p);
    void eraseAt(Point p);
    void mouseDown(bobcat::Widget*, float nx, float ny);
    void mouseDrag(bobcat::Widget*, float nx, float ny);
    void mouseUp(bobcat::Widget*, float nx, float ny);
    void undo();
    void redo();
    void clearAll();
    void bringSelectedToFront();
    void sendSelectedToBack();
    bool hasSelection() const { return static_cast<bool>(selected_); }
    std::shared_ptr<Shape> selectedShape() const { return selected_; }

    friend struct ::AppTest;
};

#endif
