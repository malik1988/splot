//
// Created by Malik on 2024/6/22.
//
#include "render_fltk.h"
#include <FL/fl_draw.H>

render_fltk::~render_fltk() = default;

void render_fltk::set_bg_color(irender::colors color)
{
    fl_color(get_color(color));
}

void render_fltk::set_fg_color(irender::colors color) {}

void render_fltk::move_to(float x, float y)
{
    fl_line(last_x_, last_y_, last_x_, last_y_);
}

void render_fltk::line_to(float x, float y)
{
    fl_line(last_x_, last_y_, (int)x, (int)y);
    last_x_ = (int)x;
    last_y_ = (int)y;
}

std::tuple<float, float> render_fltk::get_size()
{
    return std::make_tuple(w_, h_);
}

void render_fltk::draw_rect(float l_x, float l_y, float r_x, float r_y, bool fill, float radius)
{
    // if (radius > 0) {
    //     if (fill)
    //         ctx_->canvas.fill_round_rect({l_x, l_y, r_x, r_y}, radius);
    //     else
    //         ctx_->canvas.add_round_rect({l_x, l_y, r_x, r_y}, radius);
    // }
    // else {
    //     if (fill)
    //         ctx_->canvas.fill_rect({l_x, l_y, r_x, r_y});
    //     else
    //         ctx_->canvas.add_rect({l_x, l_y, r_x, r_y});
    // }
}

void render_fltk::begin_line_style(float width, irender::colors color)
{
    // ctx_->canvas.line_width(width);
    // ctx_->canvas.stroke_style(get_color(color));
}

void render_fltk::set_text_style(float font_size, irender::colors color)
{
    // ctx_->canvas.font_size(font_size);
    // ctx_->canvas.fill_style(get_color(color));
}

void render_fltk::set_text_justify(int h, int v) {}

void render_fltk::draw_text(float x, float y, const char* text)
{
    // ctx_->canvas.fill_text(text, {x, y});
}

void render_fltk::swap_buffer() {}

void render_fltk::end_line_style()
{
    fl_end_line();
}

std::tuple<float, float, float, float> render_fltk::get_bounds()
{
    // auto [x, y, h, w] = ctx_->bounds;
    return std::make_tuple(x_, y_, x_ + w_, y_ + h_);
}

void render_fltk::refresh_view()
{
    // ctx_->view.refresh(ctx_->bounds);
}

constexpr Fl_Color render_fltk::get_color(colors color)
{
    Fl_Color cr = FL_DARK1;
    switch (color) {
    case colors::BLACK: cr = FL_BLACK; break;
    case colors::DARKGRAY: cr = FL_GRAY0; break;
    case colors::LIGHTGRAY: cr = FL_GRAY; break;
    case colors::WHITE: cr = FL_WHITE; break;
    case colors::RED: cr = FL_RED; break;
    case colors::GREEN: cr = FL_GREEN; break;
    case colors::YELLOW: cr = FL_YELLOW; break;
    case colors::BLUE: cr = FL_BLUE; break;
    case colors::CYAN: cr = FL_CYAN; break;
    case colors::LIGHT_BLUE: cr = FL_BLUE; break;
    case colors::BROWN: cr = FL_DARK2; break;
    case colors::ORANGE: cr = FL_RED; break;
    case colors::PINK: cr = FL_RED; break;
    case colors::PURPLE: cr = FL_RED; break;
    default: break;
    }
    return cr;
}
