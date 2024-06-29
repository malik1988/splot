#include <elements.hpp>
#include <infra/support.hpp>
#include <iostream>

#include "eplot.h"
using namespace cycfi::elements;

auto constexpr bkd_color = rgba(35, 35, 37, 255);
auto background = box(bkd_color);
int main(int argc, char* argv[])
{
  app _app("splot example");
  window _win(_app.name());
  _win.on_close = [&_app]() { _app.stop(); };

  view view_(_win);
  // std::deque<point> _points;
  // constexpr auto per_arc=3.1415926/180;
  // for (int i=0;i<10'000;i++) {
  //     _points.emplace_back(static_cast<float>(i),static_cast<float>(std::sin(i*per_arc)*i ));
  // }
  eplot _plot;
  _plot.plot();
  view_.content(link(_plot), background);

  _app.run();
  return 0;
}
