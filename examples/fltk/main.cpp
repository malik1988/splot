// grid example
#include "fplot.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Grid.H>

auto make_button(const char* content)
{
    return new Fl_Button(0, 0, 0, 0, content);
}

int main(int argc, char** argv)
{
    int width = 500, height = 400;
    Fl::scheme("gtk+");
    auto win    = new Fl_Double_Window(width, height, "splot fltk example");
    auto ploter = new fplot(0, 0, width, height, "plot widget");

    ploter
        ->manipulator()
        // ->with_axes_mark(false)
        // ->with_grid_h(false)
        // ->with_grid_v(false)
        ->with_rect(true)
        ->with_legend(true);
    ploter->plot();
    ploter->plot_more();

    win->end();
    win->resizable(ploter);
    win->show(argc, argv);
    return Fl::run();
}