//
// Created by Malik on 2024/6/21.
//

#pragma once

#ifndef ISPLOTER_H
#    define ISPLOTER_H
#    include "irender.h"
#    include <deque>

namespace splot {
/**
 * API interface of sploter
 */
class isploter
{
public:
    enum class cursor_tracking : int8_t
    {
        entering,   // Sent when the cursor is entering
        hovering,   // Sent when the cursor is hovering
        leaving     // Sent when the cursor is leaving
    };

    enum class mouse_key : int8_t
    {
        left,
        middle,
        right
    };

    virtual ~isploter() = default;

    virtual void draw(irender* render) = 0;

    virtual bool cursor_events(irender* render, float x, float y, cursor_tracking tracking) = 0;

    virtual bool mouse_click(irender* render, float x, float y, bool down, mouse_key key) = 0;

    virtual void plot(std::deque<float> xseries, std::deque<float> yseries,
                      std::string_view name) = 0;

    virtual void plot(std::deque<float> xseries, std::function<float(float)> func,
                      std::string_view name) = 0;

    virtual isploter* with_grid_h(bool show)    = 0;
    virtual isploter* with_grid_v(bool show)    = 0;
    virtual isploter* with_axes_mark(bool show) = 0;
    virtual isploter* with_legend(bool show)    = 0;
    virtual isploter* with_rect(bool show)      = 0;
};

}   // namespace splot
#endif   // ISPLOTER_H
