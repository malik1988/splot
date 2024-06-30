//
// Created by Malik on 2024/6/30.
//

#ifndef PLOT_FLTK_H
#define PLOT_FLTK_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

class plot_fltk : public Fl_Widget
{
public:
    plot_fltk(int X, int Y, int W, int H, const char* L = 0)
        : Fl_Widget(X, Y, W, H, L)
    {}
    virtual void draw() override
    {
        // Draw background - a white filled rectangle
        fl_color(FL_RED);
        fl_rectf(x(), y(), w(), h());
        // Draw black 'X' over base widget's background
        fl_color(FL_BLACK);
        int x1 = x(), y1 = y();
        int x2 = x() + w() - 1, y2 = y() + h() - 1;
        fl_line(x1, y1, x2, y2);
        fl_line(x1, y2, x2, y1);
    }
};


#endif