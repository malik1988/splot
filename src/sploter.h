//
// Created by Malik on 2024/6/21.
//

#ifndef XPLOTER_H
#define XPLOTER_H
#include <complex>
#include <vector>

#include "../include/irender.h"
#include "../include/isploter.h"
#include "../include/sploter_data.h"

namespace splot
{
  class sploter final : public isploter
  {
   public:
    sploter()
        : show_grid_h_(true),
          show_grid_v_(true),
          show_axes_mark_(true),
          show_agend_(true),
          show_rect_(true),
          x_min_(0),
          x_max_(0),
          y_min_(0),
          y_max_(0),
          axis_mark_len_(5),
          x_scale_(1),
          y_scale_(1),
          x_(0),
          y_(0),
          x_r_(0),
          y_b_(0)
    {
    }

    ~sploter() override;

    void draw(irender *render) override;

    bool handle_events(irender *render, float x, float y, cursor_tracking tracking) override;

    bool mouse_click(irender *render, float x, float y, bool down, mouse_key key) override;

    void plot(std::deque<float> xs, std::deque<float> ys, std::string_view name) override;

    void plot(std::deque<float> xs, std::function<float(float)> func, std::string_view name) override;

   private:
    std::pair<int, float> get_divisor(float min, float max, float len);

    constexpr void calc_scales(float width, float height);

    std::pair<float, float> calc_zeros(float width, float x_divs, float x, float height, float y_divs, float y_b);

    void draw_axes(irender *render);

    void draw_curves(irender *render);

    constexpr irender::colors chose_color(int index)
    {
      switch (index)
      {
        case 1: return irender::colors::RED;
        case 2: return irender::colors::GREEN;
        case 3: return irender::colors::BLUE;
        case 4: return irender::colors::DARKGRAY;
        default: return irender::colors::BLACK;
      }
    }

    float X(float x)
    {
      return (x - x_min_) / x_scale_;
    }

    float Y(float y)
    {
      return (y - y_min_) / y_scale_;
    }

    void calc_limits()
    {
      auto calc_min_max = [](const auto &values, auto &min, auto &max)
      {
        auto [minv, maxv] = std::minmax_element(values.begin(), values.end());
        min = std::min(min, *minv), max = std::max(max, *maxv);
      };
      for (const auto &curve : curves_)
      {
        // get x min and max
        calc_min_max(curve.x, x_min_, x_max_);
        // get y min and max
        calc_min_max(curve.y, y_min_, y_max_);
      }
    }

   private:
    bool show_grid_h_, show_grid_v_;
    bool show_axes_mark_;
    bool show_agend_;
    bool show_rect_;
    bool cursor_over_, mouse_clicked_;

    // std::deque<float>
    std::vector<sploter_data> curves_;
    float x_min_, x_max_, y_min_, y_max_;
    float axis_mark_len_;
    float x_scale_, y_scale_;
    float x_, y_, x_r_, y_b_;
    float cursor_x_, cursor_y_;
    const float chouia = 0.0001;
  };
}  // namespace splot
#endif  // XPLOTER_H
