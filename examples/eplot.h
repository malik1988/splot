//
// Created by Malik on 2024/5/17.
//
#pragma once

#ifndef EPLOT_H
#define EPLOT_H

#include <elements.hpp>

#include "isploter.h"
#include "render_elements.h"

using namespace splot;
namespace cycfi::elements
{
  class eplot : public tracker<>
  {
   public:
    eplot();

    void draw(context const &ctx) override;

    void keep_tracking(context const &ctx, tracker_info &track_info) override;

    bool cursor(context const &ctx, point p, cursor_tracking status) override;

    void plot();
    void plot_more();

    auto manipulator() const
    {
      return plot_.get();
    }

   private:
    static constexpr point center(const rect &bounds)
    {
      const auto start = bounds.bottom_left();
      const auto h = bounds.height();
      return { start.x, start.y - h / 2 };
    }

   public:
    inline bool click(const context &ctx, mouse_button btn) override;

   private:
    std::unique_ptr<isploter> plot_;
    std::unique_ptr<irender> render_;
  };
}  // namespace cycfi::elements

#endif  // EPLOT_H
