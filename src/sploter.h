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

namespace splot {
class sploter final : public isploter
{
public:
    sploter()
        : show_grid_h_{true}
        , show_grid_v_{true}
        , show_axes_mark_{true}
        , show_legend_{true}
        , show_rect_{false}
        , cursor_over_{false}
        , mouse_clicked_{false}
        , x_min_{std::numeric_limits<float>::quiet_NaN()}
        , x_max_{std::numeric_limits<float>::quiet_NaN()}
        , y_min_{std::numeric_limits<float>::quiet_NaN()}
        , y_max_{std::numeric_limits<float>::quiet_NaN()}
        , real_x_min_{std::numeric_limits<float>::quiet_NaN()}
        , real_y_min_(std::numeric_limits<float>::quiet_NaN())
        , axis_mark_len_{5}
        , x_scale_{1}
        , y_scale_{1}
        , x_{0}
        , y_{0}
        , x_r_{0}
        , y_b_{0}
        , cursor_x_(0)
        , cursor_y_(0)
    {}

    ~sploter() override;

    void draw(irender* render) override;

    bool cursor_events(irender* render, float x, float y, cursor_tracking tracking) override;

    bool mouse_click(irender* render, float x, float y, bool down, mouse_key key) override;

    void plot(std::deque<float> xs, std::deque<float> ys, std::string_view name) override;

    void plot(std::deque<float> xs, std::function<float(float)> func,
              std::string_view name) override;

    isploter* with_grid_h(bool show) override
    {
        show_grid_h_ = show;
        return this;
    }

    isploter* with_grid_v(bool show) override
    {
        show_grid_v_ = show;
        return this;
    }

    isploter* with_axes_mark(bool show) override
    {
        show_axes_mark_ = show;
        return this;
    }

    isploter* with_legend(bool show) override
    {
        show_legend_ = show;
        return this;
    }

    isploter* with_rect(bool show) override
    {
        show_rect_ = show;
        return this;
    }

private:
    void draw_axes(irender* render);

    void draw_curves(irender* render);

    constexpr irender::colors chose_color(int index)
    {
        switch (index) {
        case 1: return irender::colors::BLUE;
        case 2: return irender::colors::BROWN;
        case 3: return irender::colors::ORANGE;
        case 4: return irender::colors::PINK;
        case 5: return irender::colors::GREEN;
        case 6: return irender::colors::RED;
        case 7: return irender::colors::PURPLE;
        default: return irender::colors::BLACK;
        }
    }

    float X(float x) { return (x - real_x_min_) / x_scale_; }

    float Y(float y) { return (y - real_y_min_) / y_scale_; }

    void calc_limits()
    {
        auto calc_min_max = [](const auto& values, auto& min, auto& max) {
            auto [minv, maxv] = std::minmax_element(values.begin(), values.end());
            min               = std::isnan(min) ? *minv : std::min(min, *minv),
            max               = std::isnan(max) ? *maxv : std::max(max, *maxv);
        };
        for (const auto& curve : curves_) {
            // get x min and max
            calc_min_max(curve.x, x_min_, x_max_);
            // get y min and max
            calc_min_max(curve.y, y_min_, y_max_);
        }
    }

    std::tuple<float, float, float, float> calc_range(float min, float max, float len);
    void                                   draw_empty_text(irender* render);

private:
    bool show_grid_h_, show_grid_v_;
    bool show_axes_mark_;
    bool show_legend_;
    bool show_rect_;
    bool cursor_over_, mouse_clicked_;

    std::vector<sploter_data> curves_;
    float                     x_min_, x_max_, y_min_, y_max_;
    float                     real_x_min_, real_y_min_;
    float                     axis_mark_len_;
    float                     x_scale_, y_scale_;
    float                     x_, y_, x_r_, y_b_;
    float                     cursor_x_, cursor_y_;

    // std::vector<curve_area> curves_area_;
};
}   // namespace splot
#endif   // XPLOTER_H
