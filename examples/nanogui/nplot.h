//
// Created by Malik on 2024/6/30.
//

#ifndef PLOT_FLTK_H
#define PLOT_FLTK_H

#include "isploter.h"
#include "render_nanogui.h"
#include "sploter_factory.h"


#include <nanogui/nanogui.h>

using namespace nanogui;
using namespace splot;

class nplot : public Widget
{
public:
    nplot(Widget* parent, const std::string& caption = "untitled")
        : Widget(parent)
        , caption_{caption}
        , caption_color_{Color(255, 140, 0, 255)}
        , plot_{sploter_factory::create()}
        , render_{std::make_unique<render_nanogui>()}
        , context_{0.0f, 0.0f, 0.0f, 0.0f, nullptr}
    {}
    void draw(NVGcontext* ctx) override;

    void plot();
    void plot_more();

    auto manipulator() const { return plot_.get(); }
    int  handle(int event);
    bool mouse_button_event(const Vector2i& p, int button, bool down, int modifiers) override;
    bool mouse_motion_event(const Vector2i& p, const Vector2i& rel, int button,
                            int modifiers) override;

private:
    std::string                   caption_;
    Color                         caption_color_;
    std::unique_ptr<isploter>     plot_;
    std::unique_ptr<irender>      render_;
    render_nanogui::RenderContext context_;
};

#endif
