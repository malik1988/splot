//
// Created by Malik on 2024/6/22.
//

#ifndef RENDER_NVG_H
#define RENDER_NVG_H
#include <elements.hpp>

#include "irender.h"

using namespace splot;
class render_elements final : public irender
{
public:
    explicit render_elements()
        : ctx_(nullptr)
    {}

    ~render_elements() override;

    irender* init(const void* ctx) override
    {
        ctx_ = static_cast<const cycfi::elements::context*>(ctx);
        return this;
    }

    void set_bg_color(irender::colors color) override;

    void set_fg_color(irender::colors color) override;

    void move_to(float x, float y) override;

    void line_to(float x, float y) override;

    void draw_rect(float l_x, float l_y, float r_x, float r_y, bool fill, float radius) override;

    void begin_line_style(float width, irender::colors color) override;

    void set_text_style(float font_size, irender::colors color) override;

    void set_text_justify(int h, int v) override;

    void draw_text(float x, float y, const char* text) override;

    void swap_buffer() override;

    void end_line_style() override;

    std::tuple<float, float, float, float> get_bounds() override;

    void refresh_view() override;

private:
    constexpr cycfi::elements::color get_color(irender::colors color);

    const cycfi::elements::context* ctx_;
};

#endif   // RENDER_NVG_H
