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

class fplot : public Fl_Widget
{
public:
    fplot(int X, int Y, int W, int H, const char* L = 0)
        : Fl_Widget(X, Y, W, H, L)
        , plot_{sploter_factory::create()}
        , render_{std::make_unique<render_fltk>()}
    {}
    virtual void draw() override
    {
        // fl_color(10);
        render_context ctx = {x(), y(), w(), h()};
        plot_->draw(render_->init(&ctx));
    }

    void plot();
    void plot_more();

    auto manipulator() const { return plot_.get(); }

private:
    std::unique_ptr<isploter> plot_;
    std::unique_ptr<irender>  render_;
};


#endif