//
// Created by Malik on 2024/6/21.
//

#pragma once
#ifndef SPLOTER_DATA_H
#define SPLOTER_DATA_H
#include <deque>
#include <functional>

#include "irender.h"

namespace splot {
struct sploter_data {
    /**
     *  plot data, generate curves acording to func function, like sin(x)+x*x
     * @param xseries
     * @param func function, like sin(x)+x*x
     * @param name curve name, empty will auto generate by index
     */
    explicit sploter_data(
        std::deque<float>&&         xseries,
        std::function<float(float)> func,
        std::string_view            name = "");

    /**
     *  plot data, by assgin x and y series
     * @param xseries
     * @param yseries
     * @param name curve name, empty will auto generate by index
     */
    explicit sploter_data(
        std::deque<float>&& xseries,
        std::deque<float>&& yseries,
        std::string_view    name = "");

    std::deque<float> x;
    std::deque<float> y;
    irender::colors   color;
    bool              visible;
    std::string       name;

    struct curve_area {
        float x, y, xr, yb;
        bool  visible;
    };

    /**
     * legand touch area
     * DO NOT assgin values, will bechanged by cursor and clicks
     */
    curve_area area;
};
} // namespace splot
#endif // SPLOTER_DATA_H
