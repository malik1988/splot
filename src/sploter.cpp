//
// Created by Malik on 2024/6/21.
//
#include "sploter.h"

#include <complex>
#include <iomanip>
#include <iostream>

namespace splot
{
  sploter::~sploter() = default;
  void sploter::draw(irender *render)
  {
    // clear if needed
    // switch buffer, draw in the background
    render->swap_buffer();
    draw_axes(render);
    draw_curves(render);
    render->swap_buffer();
  }

  std::pair<int, float> sploter::get_divisor(float min, float max, float len)
  {
    int div = 10;
    float smaller = 0;
    float scale = 1;
    // there are positive and negetive values,try adjust zero to the grid
    if (min < 0 && max > 0)
    {
      smaller = max < (-min) ? max : -min;
      const float total = max - min;
      div = static_cast<int>(std::ceil(total / smaller));
      scale = (smaller * div) / len;
    }
    else
    {
      const float total = max - min;
      auto abs_max = std::max(std::abs(min), std::abs(max));
      // div = static_cast<int>(std::ceil(abs_max / static_cast<int>(abs_max / 10)));
      scale = abs_max / len;
    }

    while (div < 10)
      div *= 2;
    // change to odd
    return { div, scale };
  }

  constexpr void sploter::calc_scales(float width, float height)
  {
    // set default to 1.0f
    x_scale_ = 1.0f, y_scale_ = 1.0f;
    if (0 != x_max_)
      x_scale_ = std::abs(x_max_ - x_min_) / width;
    if (0 != y_max_)
      y_scale_ = std::abs(y_max_ - y_min_) / height;
  }

  std::pair<float, float> sploter::calc_zeros(float width, float x_divs, float x, float height, float y_divs, float y_b)
  {
    float y_zero = 0, x_zero = x;
    if (y_min_ < 0)
    {
      auto i = -y_min_ / (height * y_scale_ / y_divs);
      y_zero = y_b - height / y_divs * i;
    }
    if (x_min_ < 0)
    {
      auto i = -x_min_ / (width * x_scale_ / x_divs);
      x_zero = x + width / x_divs * i;
    }
    return { x_zero, y_zero };
  }

  void sploter::draw_axes(irender *render)
  {
    // draw rectangle
    render->set_bg_color(irender::colors::WHITE);
    auto [x, y, x_r, y_b] = render->get_bounds();
    render->draw_rect(x, y, x_r, y_b, true, 0);
    constexpr float margin = 30;
    x += margin;
    y += margin;
    x_r -= margin;
    y_b -= margin;
    // save plot area points
    x_ = x, y_ = y, x_r_ = x_r, y_b_ = y_b;

    if (show_rect_)
      render->draw_rect(x, y, x_r, y_b, false, 0);

    const auto width = x_r > x ? x_r - x : x - x_r;
    const auto height = y_b > y ? y_b - y : y - y_b;
    // calc_scales(width, height);

    auto [x_divs, scale_x] = get_divisor(x_min_, x_max_, width);
    x_scale_ = scale_x;
    auto [y_divs, scale_y] = get_divisor(y_min_, y_max_, height);
    y_scale_ = scale_y;
    // draw grid
    if (show_grid_h_ || show_grid_v_)
    {
      render->begin_line_style(1, irender::colors::LIGHTGRAY);
      if (show_grid_h_)
      {
        // horizotal grid
        for (int i = y_divs - 1; i > 0; --i)
        {
          render->move_to(x, y + float(height * i) / y_divs);
          render->line_to(x_r, y + float(height * i) / y_divs);
        }
      }
      if (show_grid_v_)
      {
        // vertical grid
        for (int i = x_divs - 1; i > 0; --i)
        {
          render->move_to(x + float(width * i) / x_divs, y);
          render->line_to(x + float(width * i) / x_divs, y_b);
        }
      }
      render->end_line_style();
    }
    auto [x_zero, y_zero] = calc_zeros(width, x_divs, x, height, y_divs, y_b);

    // draw axis x and y
    {
      render->begin_line_style(1, irender::colors::BLACK);
      // axis x
      render->move_to(x, y_zero);
      render->line_to(x_r, y_zero);
      // axis y
      render->move_to(x_zero, y);
      render->line_to(x_zero, y_b);

      render->end_line_style();
    }
    if (show_axes_mark_)
    {
      // draw axes markers
      render->begin_line_style(1, irender::colors::DARKGRAY);

      // y axis markers
      for (int i = y_divs - 1; i > 0; --i)
      {
        render->move_to(x_zero, y + height * i / y_divs);
        render->line_to(x_zero + axis_mark_len_, y + height * i / y_divs);
        render->move_to(x_zero, y + height * i / y_divs);
        render->line_to(x_zero - axis_mark_len_, y + height * i / y_divs);
        // std::cout << height << " x: " << x << " y: " << y + float(height * i) / y_divs << "  \n";
      }
      // x axis markers
      for (int i = x_divs - 1; i > 0; --i)
      {
        render->move_to(x + width * i / x_divs, y_zero);
        render->line_to(x + width * i / x_divs, y_zero + axis_mark_len_);
        render->move_to(x + width * i / x_divs, y_zero);
        render->line_to(x + width * i / x_divs, y_zero - axis_mark_len_);
      }
      render->end_line_style();

      render->set_text_style(10, irender::colors::BLACK);
      // horizotal right ,vertical center
      render->set_text_justify(0, 0);
      // y axis numbers
      for (int i = 0; i <= y_divs; ++i)
      {
        auto val = y_min_ + height * y_scale_ / y_divs * i;
        if (std::fabs(val) < chouia * (y_max_ - y_min_))
          val = 0;

        std::ostringstream text;
        text << std::fixed << std::setprecision(1) << val;
        render->draw_text(x_zero - margin, y_b - height / y_divs * i, text.str().c_str());
      }
      // y zero not at the bottom,try move x axis to the y_zero position

      // x axis numbers
      render->set_text_justify(0, 0);
      for (int i = 0; i <= x_divs; ++i)
      {
        auto val = x_min_ + width * x_scale_ / x_divs * i;
        if (std::fabs(val) < chouia * (x_max_ - x_min_))
          val = 0;
        std::ostringstream text;
        text << std::fixed << std::setprecision(1) << val;
        render->draw_text(x + width / x_divs * i, y_zero + (margin / 2), text.str().c_str());
      }
      render->end_line_style();
    }
  }

  void sploter::draw_curves(irender *render)
  {
    if (curves_.empty())
      return;

    int margin = static_cast<int>(x_r_ - x_ - 30) / curves_.size();
    int index = 0;
    for (auto &[xs, ys, color, visible, name] : curves_)
    {
      ++index;
      if (show_legend_)
      {
        // draw legend box
        // select button
        std::array<float, 2> btn_x{ x_ + (index - 1) * margin - 30, x_ + (index - 1) * margin + 10 };
        std::array<float, 2> btn_y{ y_ - 20, y_ };
        if (cursor_over_ && (cursor_x_ >= btn_x[0] && cursor_x_ <= btn_x[1] + 20) &&
            (cursor_y_ >= btn_y[0] && cursor_y_ <= btn_y[1]))
        {
          if (mouse_clicked_)
            visible = !visible;

          render->set_bg_color(irender::colors::LIGHT_BLUE);
          render->draw_rect(btn_x[0], btn_y[0], btn_x[1], btn_y[1], true, 5.0f);
        }

        render->begin_line_style(2, visible ? chose_color(index) : irender::colors::DARKGRAY);
        // colored title
        render->set_text_style(14, visible ? chose_color(index) : irender::colors::DARKGRAY);
        if (name.empty())
        {
          // set name to default "curve i"
          std::stringstream ss;
          ss << "curve" << index;
          render->draw_text(x_ + (index - 1) * margin, y_ - 10, ss.str().c_str());
        }
        else
        {
          render->draw_text(x_ + (index - 1) * margin, y_ - 10, name.c_str());
        }
        // legend colored line
        render->move_to(x_ + (index - 1) * margin, y_ - 10);
        render->line_to(x_ + (index - 1) * margin - 20, y_ - 10);
        render->end_line_style();
      }
      if (!visible)
      {
        continue;
      }
      render->begin_line_style(2, chose_color(index));
      auto first = true;
      const auto it_x = xs.begin();
      const auto it_y = ys.begin();
      for (auto i = 0; i < xs.size(); ++i)
      {
        if (first)
        {
          first = false;
          render->move_to(x_ + X(*(it_x + i)), y_b_ - Y(*(it_y + i)));
        }
        else
        {
          render->line_to(x_ + X(*(it_x + i)), y_b_ - Y(*(it_y + i)));
        }
      }

      render->end_line_style();
    }
  }

  bool sploter::mouse_click(irender *, float, float, const bool down, const mouse_key key)
  {
    if (key == mouse_key::left)
    {
      mouse_clicked_ = down;
    }
    return true;
  }

  bool sploter::handle_events(irender *render, float x, float y, cursor_tracking tracking)
  {
    cursor_x_ = x, cursor_y_ = y;
    switch (tracking)
    {
      case cursor_tracking::hovering:
      case cursor_tracking::entering:
        cursor_over_ = true;
        render->refresh_view();
        break;
      case cursor_tracking::leaving:
        cursor_over_ = false;
        render->refresh_view();
        break;
      default: break;
    }
    return true;
  }

  void sploter::plot(std::deque<float> xseries, std::deque<float> yseries, std::string_view name)
  {
    curves_.emplace_back(std::move(xseries), std::move(yseries), name);
    calc_limits();
  }
  void sploter::plot(std::deque<float> xseries, std::function<float(float)> func, std::string_view name)
  {
    curves_.emplace_back(std::move(xseries), func, name);
    calc_limits();
  }
}  // namespace splot