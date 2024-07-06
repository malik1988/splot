//
// Created by Malik on 2024/6/22.
//

#pragma once

#ifndef RENDER_NANOGUI_H
#    define RENDER_NANOGUI_H

#    include "irender.h"
#    include "nanogui/nanogui.h"

using namespace splot;
using namespace nanogui;
class render_nanogui final : public irender
{
public:
    ~render_nanogui() override;

    irender* init(const void* ctx) override;

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

    struct RenderContext
    {
        float x,y,w,h;
        NVGcontext* ctx;
    };
private:
    Color get_color(irender::colors color);
    RenderContext *context_;
};



#endif   // RENDER_NANOGUI_H
