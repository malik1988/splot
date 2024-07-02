//
// Created by Malik on 2024/6/30.
//

#ifndef PLOT_FLTK_H
#define PLOT_FLTK_H

#include "isploter.h"
#include "render_fltk.h"
#include "sploter_factory.h"


#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

using namespace splot;

class plot_fltk : public Fl_Widget
{
public:
    plot_fltk(int X, int Y, int W, int H, const char* L = 0)
        : Fl_Widget(X, Y, W, H, L)
        , sploter_{sploter_factory::create()}
        , render_{std::make_unique<render_fltk>()}
    {}
    virtual void draw() override
    {
        // fl_color(10);
        render_context ctx = {x(), y(), w(), h()};
        sploter_->draw(render_->init(&ctx));
    }


    void eplot::plot()
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

    void eplot::plot_more()
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

private:
    std::unique_ptr<isploter> sploter_;
    std::unique_ptr<irender>  render_;
};


#endif