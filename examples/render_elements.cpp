//
// Created by Malik on 2024/6/22.
//
#include "render_elements.h"

render_elements::~render_elements() = default;

void render_elements::set_bg_color(irender::colors color)
{
  ctx_->canvas.fill_style(get_color(color));
}

void render_elements::set_fg_color(irender::colors color)
{
  ctx_->canvas.stroke_style(get_color(color));
}

void render_elements::move_to(float x, float y)
{
  ctx_->canvas.move_to({ x, y });
}

void render_elements::line_to(float x, float y)
{
  ctx_->canvas.line_to({ x, y });
}

std::tuple<float, float> render_elements::get_size()
{
  auto [w, h] = ctx_->bounds.size();
  return std::make_tuple(h, w);
}

void render_elements::draw_rect(float l_x, float l_y, float r_x, float r_y, bool fill, float radius)
{
  if (radius > 0)
  {
    if (fill)
      ctx_->canvas.fill_round_rect({ l_x, l_y, r_x, r_y }, radius);
    else
      ctx_->canvas.add_round_rect({ l_x, l_y, r_x, r_y }, radius);
  }
  else
  {
    if (fill)
      ctx_->canvas.fill_rect({ l_x, l_y, r_x, r_y });
    else
      ctx_->canvas.add_rect({ l_x, l_y, r_x, r_y });
  }
}

void render_elements::begin_line_style(float width, irender::colors color)
{
  ctx_->canvas.line_width(width);
  ctx_->canvas.stroke_style(get_color(color));
}

void render_elements::set_text_style(float font_size, irender::colors color)
{
  ctx_->canvas.font_size(font_size);
  ctx_->canvas.fill_style(get_color(color));
}

void render_elements::set_text_justify(int h, int v)
{
}

void render_elements::draw_text(float x, float y, const char *text)
{
  ctx_->canvas.fill_text(text, { x, y });
}

void render_elements::swap_buffer()
{
}

void render_elements::end_line_style()
{
  ctx_->canvas.stroke();
}

std::tuple<float, float, float, float> render_elements::get_bounds()
{
  auto [x, y, h, w] = ctx_->bounds;
  return std::make_tuple(x, y, h, w);
}

void render_elements::refresh_view()
{
  ctx_->view.refresh(ctx_->bounds);
}

constexpr cycfi::elements::color render_elements::get_color(colors color)
{
  namespace el = cycfi::elements;
  el::color cr = el::colors::white_smoke;
  switch (color)
  {
    case colors::BLACK: cr = el::colors::black; break;
    case colors::DARKGRAY: cr = el::colors::dark_slate_gray; break;
    case colors::LIGHTGRAY: cr = el::colors::light_gray.opacity(0.6); break;
    case colors::WHITE: cr = el::colors::white; break;
    case colors::RED: cr = el::colors::red; break;
    case colors::GREEN: cr = el::colors::green; break;
    case colors::YELLOW: cr = el::colors::yellow; break;
    case colors::BLUE: cr = el::colors::blue; break;
    case colors::CYAN: cr = el::colors::cyan; break;
    case colors::LIGHT_BLUE: cr = el::colors::light_blue.opacity(0.8); break;
    case colors::BROWN: cr = el::colors::brown; break;
    case colors::ORANGE: cr = el::colors::orange; break;
    case colors::PINK: cr = el::colors::pink; break;
    case colors::PURPLE: cr = el::colors::purple; break;
    default:break;
  }
  return cr;
}
