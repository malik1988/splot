//
// Created by Malik on 2024/6/22.
//
#include "render_nanogui.h"
#include <nanogui/opengl.h>

render_nanogui::~render_nanogui() = default;
irender* render_nanogui::init(const void* context)
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
    nvgText(context_->ctx, x, y, text, nullptr);
}

void render_nanogui::swap_buffer() {}

void render_nanogui::end_line_style()
{
    nvgStroke(context_->ctx);
}

std::tuple<float, float, float, float> render_nanogui::get_bounds()
{
    return std::make_tuple(
        context_->x, context_->y, context_->x + context_->w, context_->y + context_->h);
}

void render_nanogui::refresh_view() {}

Color render_nanogui::get_color(irender::colors color)
{
    Color cr;
    switch (color) {
    case colors::BLACK: cr = Color(0, 0, 0, 255); break;
    case colors::DARKGRAY: cr = Color(47, 79, 79, 255); break;
    case colors::LIGHTGRAY: cr = Color(168, 168, 168, 255); break;
    case colors::WHITE: cr = Color(255, 255, 255, 255); break;
    case colors::RED: cr = Color(255, 0, 0, 255); break;
    case colors::GREEN: cr = Color(0, 255, 0, 255); break;
    case colors::YELLOW: cr = Color(255, 255, 0, 255); break;
    case colors::BLUE: cr = Color(0, 0, 255, 255); break;
    case colors::CYAN: cr = Color(0, 255, 255, 1); break;
    case colors::LIGHT_BLUE: cr = Color(173, 216, 230, 0.8 * 255); break;
    case colors::BROWN: cr = Color(165, 42, 42, 255); break;
    case colors::ORANGE: cr = Color(255, 140, 0, 255); break;
    case colors::PINK: cr = Color(255, 20, 147, 255); break;
    case colors::PURPLE: cr = Color(147, 112, 219, 255); break;
    default: break;
    }
    return cr;
}
