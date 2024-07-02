//
// Created by Malik on 2024/5/17.
//

#include "eplot.h"

#include "sploter_factory.h"
namespace cycfi::elements {
eplot::eplot()
    : plot_{sploter_factory::create()}
    , render_{new render_elements()}
{}
void eplot::draw(context const& ctx)
{
    plot_->draw(render_->init(&ctx));
}

void eplot::keep_tracking(context const& ctx, tracker_info& track_info)
{
    tracker<>::keep_tracking(ctx, track_info);
}

bool eplot::cursor(context const& ctx, point p, cursor_tracking status)
{
    return plot_->handle_events(
        render_->init(&ctx), p.x, p.y, static_cast<isploter::cursor_tracking>(status));
}

bool eplot::click(const context& ctx, mouse_button btn)
{
    tracker<>::click(ctx, btn);
    return plot_->mouse_click(render_->init(&ctx),
                              btn.pos.x,
                              btn.pos.y,
                              btn.down,
                              static_cast<isploter::mouse_key>(btn.state));
}

void eplot::plot()
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

void eplot::plot_more()
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
}   // namespace cycfi::elements
