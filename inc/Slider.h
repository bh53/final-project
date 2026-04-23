#ifndef COLOR_SLIDER_H
#define COLOR_SLIDER_H

#include <bobcat_ui/bobcat_ui.h>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <algorithm>
#include <functional>
#include <string>

class ColorSlider : public Fl_Widget {
    std::string caption;
    int value_;
    int max_;
    Fl_Color barColor_;
    std::function<void(bobcat::Widget*)> onChangeCb;

    int clampValue(int v) const {
        if (v < 0) return 0;
        if (v > max_) return max_;
        return v;
    }

    void setFromX(int px) {
        int left = x() + 10;
        int right = x() + w() - 10;
        int span = right - left;
        if (span <= 0) return;
        int raw = (px - left) * max_ / span;
        value_ = clampValue(raw);
        redraw();
        if (onChangeCb) onChangeCb(reinterpret_cast<bobcat::Widget*>(this));
    }

public:
    ColorSlider(int X, int Y, int W, int H, const std::string& label, Fl_Color barColor)
        : Fl_Widget(X, Y, W, H, label.c_str()), caption(label), value_(0), max_(255), barColor_(barColor) {
        box(FL_FLAT_BOX);
    }

    int value() const { return value_; }
    void value(int v) {
        value_ = clampValue(v);
        redraw();
    }

    void onChange(std::function<void(bobcat::Widget*)> cb) {
        onChangeCb = cb;
    }

    int handle(int event) override {
        switch (event) {
            case FL_PUSH:
            case FL_DRAG:
                setFromX(Fl::event_x());
                return 1;
            default:
                break;
        }
        return Fl_Widget::handle(event);
    }

    void draw() override {
        fl_push_clip(x(), y(), w(), h());
        fl_color(fl_rgb_color(235, 235, 235));
        fl_rectf(x(), y(), w(), h());
        fl_color(fl_rgb_color(130, 130, 130));
        fl_rect(x(), y(), w(), h());

        int left = x() + 10;
        int right = x() + w() - 10;
        int barY = y() + h() / 2 - 4;
        int barH = 8;
        int span = right - left;
        int fillW = span > 0 ? (value_ * span) / max_ : 0;

        fl_color(fl_rgb_color(200, 200, 200));
        fl_rectf(left, barY, span, barH);
        fl_color(barColor_);
        fl_rectf(left, barY, fillW, barH);
        fl_color(FL_BLACK);
        fl_rect(left, barY, span, barH);

        int knobX = left + fillW;
        fl_color(fl_rgb_color(40, 40, 40));
        fl_pie(knobX - 6, y() + h() / 2 - 6, 12, 12, 0, 360);

        fl_color(FL_BLACK);
        fl_font(FL_HELVETICA, 12);
        std::string text = caption + ": " + std::to_string(value_);
        fl_draw(text.c_str(), x() + 6, y() + 14);
        fl_pop_clip();
    }
};

#endif
