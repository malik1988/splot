//
// Created by Malik on 2024/6/22.
//
#include "render_fltk.h"

#include "FL/forms.H"

#include <FL/fl_draw.H>

render_fltk::~render_fltk() = default;
irender*      render_fltk::init(const void* context)
{
    auto ctx = (render_context*)(context);
    x_       = ctx->x;
    y_       = ctx->y;
    w_       = ctx->w;
    h_       = ctx->h;
    parent_  = ctx->widget;
    return this;
}

void render_fltk::set_bg_color(irender::colors color)
{
    last_color_ = get_color(color);
    fl_color(last_color_);
}

void render_fltk::set_fg_color(irender::colors color)
{
    last_color_ = get_color(color);
    fl_color(last_color_);
}

void render_fltk::move_to(float x, float y)
{
    last_x_ = static_cast<int>(x), last_y_ = static_cast<int>(y);
}

void render_fltk::line_to(float x, float y)
{
    fl_line(last_x_, last_y_, static_cast<int>(x), static_cast<int>(y));
    last_x_ = static_cast<int>(x);
    last_y_ = static_cast<int>(y);
}

void render_fltk::draw_rect(float l_x, float l_y, float r_x, float r_y, bool fill, float radius)
{
    auto x = static_cast<int>(l_x);
    auto y = static_cast<int>(l_y);
    auto w = static_cast<int>(r_x - l_x);
    auto h = static_cast<int>(r_y - l_y);

    if (radius > 0) {
        if (fill)
            fl_rounded_rectf(x, y, w, h, (int)radius);
        else
            fl_rounded_rect(x, y, w, h, radius);
    }
    else {
        if (fill)
            fl_rectf(x, y, w, h, last_color_);
        else
            fl_rect(x, y, w, h);
    }
}

void render_fltk::begin_line_style(float width, irender::colors color)
{
    set_fg_color(color);
    fl_line_style(FL_SOLID, static_cast<int>(width));
}

void render_fltk::set_text_style(float font_size, irender::colors color)
{
    set_fg_color(color);
    fl_font(font_, static_cast<Fl_Fontsize>(font_size));
}

void render_fltk::set_text_justify(int h, int v) {}

void render_fltk::draw_text(float x, float y, const char* text)
{
    fl_draw(text, static_cast<int>(x), static_cast<int>(y));
}

void render_fltk::swap_buffer() {}

void render_fltk::end_line_style()
{
    fl_end_line();
}

std::tuple<float, float, float, float> render_fltk::get_bounds()
{
    return std::make_tuple(x_, y_, x_ + w_, y_ + h_);
}

void render_fltk::refresh_view()
{
    fl_redraw_object(parent_);
}

constexpr Fl_Color render_fltk::get_color(colors color)
{
    Fl_Color cr = FL_DARK1;
    switch (color) {
    case colors::BLACK: cr = FL_BLACK; break;
    case colors::DARKGRAY: cr = fl_rgb_color(47, 79, 79); break;
    case colors::LIGHTGRAY: cr = fl_rgb_color(168, 168, 168); break;
    case colors::WHITE: cr = FL_WHITE; break;
    case colors::RED: cr = FL_RED; break;
    case colors::GREEN: cr = FL_GREEN; break;
    case colors::YELLOW: cr = FL_YELLOW; break;
    case colors::BLUE: cr = FL_BLUE; break;
    case colors::CYAN: cr = FL_CYAN; break;
    case colors::LIGHT_BLUE: cr = 	fl_rgb_color(173, 216, 230); break;
    case colors::BROWN: cr = fl_rgb_color(165, 42, 42); break;
    case colors::ORANGE: cr = fl_rgb_color(255, 140, 0); break;
    case colors::PINK: cr = fl_rgb_color(255, 20, 147); break;
    case colors::PURPLE: cr = fl_rgb_color(147, 112, 219); break;
    default: break;
    }
    return cr;
}
