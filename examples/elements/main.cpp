#include <elements.hpp>
#include <infra/support.hpp>
#include <iostream>

#include "eplot.h"
using namespace cycfi::elements;

auto constexpr bkd_color = rgba(35, 35, 37, 255);
auto background          = box(bkd_color);
int  main(int argc, char* argv[])
{
    app    _app("splot example");
    window _win(_app.name());
    _win.on_close = [&_app]() { _app.stop(); };

    view view_(_win);

    eplot _plot;
    // clear some extra symbols to accelerate, will only effect after redraw cause manually.
    _plot.manipulator()->with_axes_mark(true)->with_legend(true)->with_rect(false);
    // add more curves
    _plot.plot();
    // add more curves
    _plot.plot_more();
    view_.content(link(_plot), background);

    _app.run();
    return 0;
}