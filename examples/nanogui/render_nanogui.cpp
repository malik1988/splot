//
// Created by Malik on 2024/6/22.
//
#include "render_nanogui.h"
#include <nanogui/opengl.h>

render_nanogui::~render_nanogui() = default;
irender*         render_nanogui::init(const void* context)
{
    context_ = (RenderContext*)context;
    return this;
}

void render_nanogui::set_bg_color(irender::colors color)
{
    nvgFillColor(context_->ctx, get_color(color));
}

void render_nanogui::set_fg_color(irender::colors color)
{
    nvgStrokeColor(context_->ctx, get_color(color));
}

void render_nanogui::move_to(float x, float y)
{
    nvgBeginPath(context_->ctx);
    nvgMoveTo(context_->ctx, x, y);
}

void render_nanogui::line_to(float x, float y)
{
    nvgLineTo(context_->ctx, x, y);
}

void render_nanogui::draw_rect(float l_x, float l_y, float r_x, float r_y, bool fill, float radius)
{
    nvgBeginPath(context_->ctx);
    if (radius > 0) {
        nvgRoundedRect(context_->ctx, l_x, l_y, r_x, r_y, radius);
    }
    else {
        nvgRect(context_->ctx, l_x, l_y, r_x, r_y);
    }
    if (fill) {
        nvgFill(context_->ctx);
    }
}

void render_nanogui::begin_line_style(float width, irender::colors color)
{
    nvgStrokeColor(context_->ctx, get_color(color));
}

void render_nanogui::set_text_style(float font_size, irender::colors color)
{
    nvgFontSize(context_->ctx, font_size);
    nvgTextAlign(context_->ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_BOTTOM);
    nvgFillColor(context_->ctx, get_color(color));
}

void render_nanogui::set_text_justify(int h, int v) {}

void render_nanogui::draw_text(float x, float y, const char* text)
{
    nvgText(context_->ctx,x,y,text,nullptr);
}

void render_nanogui::swap_buffer() {}

void render_nanogui::end_line_style()
{
    nvgStroke(context_->ctx);
}

std::tuple<float, float, float, float> render_nanogui::get_bounds()
{
    return std::make_tuple(context_->x,context_->y,context_->x+context_->w,context_->y+context_->h);
}

void render_nanogui::refresh_view() {}

Color render_nanogui::get_color(irender::colors color)
{
    Color cr;
    // switch (color) {
    // case colors::BLACK: cr = Colors; break;
    // case colors::DARKGRAY: cr = fl_rgb_color(47, 79, 79); break;
    // case colors::LIGHTGRAY: cr = fl_rgb_color(168, 168, 168); break;
    // case colors::WHITE: cr = FL_WHITE; break;
    // case colors::RED: cr = FL_RED; break;
    // case colors::GREEN: cr = FL_GREEN; break;
    // case colors::YELLOW: cr = FL_YELLOW; break;
    // case colors::BLUE: cr = FL_BLUE; break;
    // case colors::CYAN: cr = FL_CYAN; break;
    // case colors::LIGHT_BLUE: cr = 	fl_rgb_color(173, 216, 230); break;
    // case colors::BROWN: cr = fl_rgb_color(165, 42, 42); break;
    // case colors::ORANGE: cr = fl_rgb_color(255, 140, 0); break;
    // case colors::PINK: cr = fl_rgb_color(255, 20, 147); break;
    // case colors::PURPLE: cr = fl_rgb_color(147, 112, 219); break;
    // default: break;
    // }
    return cr;
}
