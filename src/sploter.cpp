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

    auto [y_divs, y_real_min, y_zero_offset, y_scale] = calc_range(y_min_, y_max_, height);
    y_scale_ = y_scale;
    real_y_min_ = y_real_min;
    auto [x_divs, x_real_min, x_zero_offset, x_scale] = calc_range(x_min_, x_max_, width);
    x_scale_ = x_scale;
    real_x_min_ = x_real_min;

    if (show_grid_h_ || show_grid_v_)
    {
      render->begin_line_style(1, irender::colors::LIGHTGRAY);
      if (show_grid_h_)
      {  // horizotal grid
        for (int i = (int)y_divs - 1; i > 0; --i)
        {
          render->move_to(x, y + float(height * i) / y_divs);
          render->line_to(x_r, y + float(height * i) / y_divs);
        }
      }
      if (show_grid_v_)
      {  // vertical grid
        for (int i = (int)x_divs - 1; i > 0; --i)
        {
          render->move_to(x + float(width * i) / x_divs, y);
          render->line_to(x + float(width * i) / x_divs, y_b);
        }
      }
      render->end_line_style();
    }

    auto y_zero = y_b + y_zero_offset / y_scale;
    auto x_zero = x - x_zero_offset / x_scale;
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
      {
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
      }
      //------
      // axis numbers
      {
        render->set_text_style(10, irender::colors::BLACK);
        // horizotal right ,vertical center
        render->set_text_justify(0, 0);
        // y axis numbers
        for (int i = 0; i <= y_divs; ++i)
        {
          auto val = y_real_min + height * y_scale_ / y_divs * i;

          std::ostringstream text;
          text << std::fixed << std::setprecision(1) << val;
          render->draw_text(x_zero - margin, y_b - height / y_divs * i, text.str().c_str());
        }
        // y zero not at the bottom,try move x axis to the y_zero position

        // x axis numbers
        render->set_text_justify(0, 0);
        for (int i = 0; i <= x_divs; ++i)
        {
          auto val = x_real_min + width * x_scale_ / x_divs * i;

          std::ostringstream text;
          text << std::fixed << std::setprecision(1) << val;
          render->draw_text(x + width / x_divs * i, y_zero + (margin / 2), text.str().c_str());
        }
        render->end_line_style();
      }
    }
  }

  void sploter::draw_curves(irender *render)
  {
    if (curves_.empty())
      return;
    constexpr float padding=15;
    constexpr float button_size=40;
    int margin = static_cast<int>(x_r_ - x_) / curves_.size();
    int index = 0;
    for (auto &[xs, ys, color, visible, name] : curves_)
    {
      ++index;
      if (show_legend_)
      {
        // draw legend box
        // select button
        auto [btn_x, btn_x_r, btn_y, btn_y_b] = std::tuple<float, float, float, float>{
          x_ + padding+ (index - 1) * margin ,
          x_ +padding+button_size+ (index - 1) * margin ,
          y_ - padding,
          y_
        };
        if (cursor_over_ && (cursor_x_ >= btn_x && cursor_x_ <= btn_x_r + 20) &&
            (cursor_y_ >= btn_y && cursor_y_ <= btn_y_b))
        {
          if (mouse_clicked_)
            visible = !visible;

          render->set_bg_color(irender::colors::LIGHT_BLUE);
          render->draw_rect(btn_x,btn_y,btn_x_r,btn_y_b, true, 5.0f);
        }

        render->begin_line_style(2, visible ? chose_color(index) : irender::colors::DARKGRAY);
        // colored title
        render->set_text_style(14, visible ? chose_color(index) : irender::colors::DARKGRAY);
        if (name.empty())
        {
          // set name to default "curve i"
          std::stringstream ss;
          ss << "curve" << index;
          render->draw_text(x_+padding + (index - 1) * margin, y_-padding, ss.str().c_str());
        }
        else
        {
          render->draw_text(x_+padding + (index - 1) * margin, y_ -padding, name.c_str());
        }
        // legend colored line
        render->move_to(x_ +padding+ (index - 1) * margin, y_ -padding+5);
        render->line_to(x_ +padding+button_size+ (index - 1) * margin, y_ -padding+ 5);
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

  std::tuple<float, float, float, float> sploter::calc_range(float min, float max, float len)
  {
    auto min10 = [](float x)
    {
      auto c10 = std::log10(std::abs(x));
      auto p10 = std::pow(10, c10 - 1);
      if (x == 0)
      {
        return 0.0F;
      }
      if (x > 0)
      {
        return static_cast<float>(std::floor(x / p10) * p10);
      }
      return static_cast<float>(-std::ceil(-x / p10) * p10);
    };

    auto max10 = [](float x)
    {
      auto c10 = std::log10(std::abs(x));
      auto p10 = std::pow(10, c10 - 1);
      if (x == 0)
      {
        return 0.0F;
      }
      if (x > 0)
      {
        return static_cast<float>(std::ceil(x / p10) * p10);
      }
      return static_cast<float>(-std::floor(-x / p10) * p10);
    };

    auto v_max10 = max10(max);
    auto v_min10 = min10(min);
    auto v_range = v_max10 - v_min10;
    constexpr auto c_div = 10;
    auto v_div = v_range / c_div;
    float real_v_div = v_div;
    if (v_div > 10)
    {
      real_v_div = std::ceil(v_div / 10) * 10;
    }
    else if (v_div > 5)
    {
      real_v_div = std::ceil(v_div / 5) * 5;
    }
    else if (v_div > 2)
    {
      real_v_div = std::ceil(v_div / 5) * 5;
    }
    else if (v_div > 1)
    {
      real_v_div = std::ceil(v_div);
    }

    float real_c_total, real_len, scale, real_min, zero_offset;
    if (min < 0 && max > 0)
    {
      auto real_c_max = std::ceil(std::abs(max) / real_v_div);
      auto real_c_min = std::ceil(std::abs(min) / real_v_div);
      real_c_total = real_c_max + real_c_min;
      real_min = -real_c_min * real_v_div;

      real_len = real_v_div * real_c_total;
      scale = real_len / len;
      zero_offset = real_min;
    }
    else if (max <= 0)
    {  // all negetive values
      auto real_c_max = std::floor(-max / real_v_div);
      auto real_c_min = std::ceil(-min / real_v_div);
      real_c_total = std::abs(real_c_max - real_c_min);
      real_min = -real_c_min * real_v_div;

      real_len = real_v_div * real_c_total;
      scale = real_len / len;
      zero_offset = -real_c_min;
    }
    else
    {  // all postive values
      auto real_c_max = std::ceil(max / real_v_div);
      auto real_c_min = std::floor(min / real_v_div);
      real_c_total = std::abs(real_c_max - real_c_min);
      real_min = real_c_min * real_v_div;

      real_len = real_v_div * real_c_total;
      scale = real_len / len;
      zero_offset = real_c_min;
    }

    return { real_c_total, real_min, zero_offset, scale };
  }
}  // namespace splot