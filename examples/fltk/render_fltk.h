//
// Created by Malik on 2024/6/22.
//

#pragma once

#ifndef RENDER_FLTK_H
#    define RENDER_FLTK_H

#    include "irender.h"
#    include <FL/Fl.H>

using namespace splot;
class render_fltk final : public irender
{
public:
    // explicit render_fltk(int x, int y, int w, int h)
    //     : x_{x}
    //     , y_{y}
    //     , w_{w}
    //     , h_{h}
    // {}

    ~render_fltk() override;

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

private:
    constexpr Fl_Color get_color(irender::colors color);
    int                last_x_, last_y_;
    int                x_, y_, w_, h_;
    Fl_Color           last_color_;
    Fl_Widget*         parent_;
    Fl_Font            font_;
};

struct render_context
{
    int x, y, w, h;
    Fl_Widget* widget;
};
#endif   // RENDER_FLTK_H
