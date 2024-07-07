//
// Created by Malik on 2024/7/2.
//
#include "nplot.h"

#include <nanogui/opengl.h>
#include <sstream>

void nplot::draw(NVGcontext* ctx)
{
    Widget::draw(ctx);


    nvgBeginPath(ctx);
    nvgFontFace(ctx, "sans");
    if (!caption_.empty()) {
        nvgFontSize(ctx, 14.0f);
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgFillColor(ctx, caption_color_);
        nvgText(ctx, m_pos.x() + 3, m_pos.y() + 1, caption_.c_str(), NULL);
    }
    auto title_margin = 20.0f;
    context_.x        = m_pos.x() + title_margin;
    context_.y        = m_pos.y() + title_margin;
    context_.w        = m_size.x() - title_margin * 2;
    context_.h        = m_size.y() - title_margin * 2;
    context_.ctx      = ctx;
    plot_->draw(render_->init(&context_));
}
void nplot::plot()
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

void nplot::plot_more()
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
int nplot::handle(int event)
{
    // render_context ctx = {x(), y(), w(), h(), this};
    //
    // const int x       = Fl::event_x();
    // const int y       = Fl::event_y();
    // bool      handled = false;
    // switch (event) {
    // case FL_MOVE:
    //     plot_->handle_events(render_->init(&ctx), x, y, isploter::cursor_tracking::entering);
    //     handled = true;
    //     break;
    // case FL_ENTER:
    //     handled = true;
    //     break;
    // case FL_LEAVE:
    //     plot_->handle_events(render_->init(&ctx), x, y, isploter::cursor_tracking::leaving);
    //     handled = true;
    //     break;
    //
    // case FL_PUSH:
    //     plot_->mouse_click(render_->init(&ctx), x, y, true, isploter::mouse_key::left);
    //     handled = true;
    //     break;
    // case FL_RELEASE:
    //     plot_->mouse_click(render_->init(&ctx), x, y, false, isploter::mouse_key::left);
    //     handled = true;
    //     break;
    // }
    // if (handled) {
    //     return 1;
    // }
    // return Fl_Widget::handle(event);
    return 0;
}
bool nplot::mouse_button_event(const Vector2i& p, int button, bool down, int modifiers)
{
    return Widget::mouse_button_event(p, button, down, modifiers);
}
bool nplot::mouse_motion_event(const Vector2i& p, const Vector2i& rel, int button, int modifiers)
{
    return Widget::mouse_motion_event(p, rel, button, modifiers);
}