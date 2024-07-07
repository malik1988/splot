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

bool nplot::mouse_button_event(const Vector2i& p, int button, bool down, int modifiers)
{
    auto ret = Widget::mouse_button_event(p, button, down, modifiers);
    if (button == GLFW_MOUSE_BUTTON_1)
        return plot_->mouse_click(
            render_->init(&context_), p.x(), p.y(), down, isploter::mouse_key::left);
    return ret;
}
bool nplot::mouse_motion_event(const Vector2i& p, const Vector2i& rel, int button, int modifiers)
{
    auto ret = Widget::mouse_motion_event(p, rel, button, modifiers);
    if (button == GLFW_MOUSE_BUTTON_1)
        return plot_->cursor_events(render_->init(&context_),
                                    p.x(),
                                    p.y(),
                                    static_cast<isploter::cursor_tracking>(modifiers));
    return ret;
}