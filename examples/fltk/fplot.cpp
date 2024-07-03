//
// Created by Malik on 2024/7/2.
//
#include "fplot.h"

#include <sstream>

void fplot::draw()
{
    // fl_color(10);
    render_context ctx = {x(), y(), w(), h(), this};
    plot_->draw(render_->init(&ctx));
}
void fplot::plot()
{
    for (int c = 1; c <= 3; ++c) {
        std::deque<float> vs;
        for (int i = 100; i < 1'000; i++) {
            vs.emplace_back(i * 1.0);
        }
        std::ostringstream ss;
        ss << 10 * c << "sin(x[100,1000])";
        plot_->plot(
            vs,
            [c](float x) {
                constexpr auto arc = static_cast<float>(3.1415 / 180);
                x *= arc;
                return std::sin(x) * static_cast<float>(c * 10.0F);
            },
            ss.str());
    }
}

void fplot::plot_more()
{
    for (int c = 1; c <= 3; ++c) {
        std::deque<float> vs;
        for (int i = -500; i < 1'000; i++) {
            vs.emplace_back(i * 1.0);
        }
        std::ostringstream ss;
        ss << c << "xsin(x[-500,1000])";
        plot_->plot(
            vs,
            [c](float x) {
                constexpr auto arc = static_cast<float>(3.1415 / 180);
                x *= arc;
                return std::sin(x) * x * static_cast<float>(c);
            },
            ss.str());
    }
}
int fplot::handle(int event)
{
    render_context ctx = {x(), y(), w(), h(), this};

    const int x       = Fl::event_x();
    const int y       = Fl::event_y();
    bool      handled = false;
    switch (event) {
    case FL_MOVE:
        plot_->handle_events(render_->init(&ctx), x, y, isploter::cursor_tracking::entering);
        handled = true;
        break;
    case FL_ENTER:
        handled = true;
        break;
    case FL_LEAVE:
        plot_->handle_events(render_->init(&ctx), x, y, isploter::cursor_tracking::leaving);
        handled = true;
        break;

    case FL_PUSH:
        plot_->mouse_click(render_->init(&ctx), x, y, true, isploter::mouse_key::left);
        handled = true;
        break;
    case FL_RELEASE:
        plot_->mouse_click(render_->init(&ctx), x, y, false, isploter::mouse_key::left);
        handled = true;
        break;
    }
    if (handled) {
        return 1;
    }
    return Fl_Widget::handle(event);
}