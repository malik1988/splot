//
// Created by Malik on 2024/7/2.
//
#include "fplot.h"

#include <sstream>

void fplot::plot()
{
    for (int c = 1; c <= 3; ++c) {
        std::deque<float> vs;
        for (int i = 100; i < 1'000; i++) {
            vs.emplace_back(i * 1.0);
        }
        std::ostringstream ss;
        ss << 10 * c << "sin(x[100,1000])";
        plot_->plot(
            vs,
            [c](float x) {
                constexpr auto arc = static_cast<float>(3.1415 / 180);
                x *= arc;
                return std::sin(x) * static_cast<float>(c * 10.0F);
            },
            ss.str());
    }
}

void fplot::plot_more()
{
    for (int c = 1; c <= 3; ++c) {
        std::deque<float> vs;
        for (int i = -500; i < 1'000; i++) {
            vs.emplace_back(i * 1.0);
        }
        std::ostringstream ss;
        ss << c << "xsin(x[-500,1000])";
        plot_->plot(
            vs,
            [c](float x) {
                constexpr auto arc = static_cast<float>(3.1415 / 180);
                x *= arc;
                return std::sin(x) * x * static_cast<float>(c);
            },
            ss.str());
    }
}