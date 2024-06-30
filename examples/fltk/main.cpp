// grid example
#include "plot_fltk.h"
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

    Fl::scheme("gtk+");
    auto win    = new Fl_Double_Window(320, 180, "3x3 Fl_Grid with Buttons");
    auto ploter = new plot_fltk(3, 3, 10, 10);
    // create the Fl_Grid container with five buttons
    auto grid = new Fl_Grid(0, 0, win->w(), win->h());
    grid->layout(3, 3, 10, 10);
    grid->color(FL_WHITE);
    auto b0 = make_button("New");
    auto b1 = make_button("Options");
    auto b3 = make_button("About");
    auto b4 = make_button("Help");
    auto b6 = make_button("Quit");
    // assign buttons to grid positions
    grid->widget(b0, 0, 0);
    grid->widget(b1, 0, 2);
    grid->widget(b3, 1, 1);
    grid->widget(b4, 2, 0);
    grid->widget(b6, 2, 2);
    // grid->show_grid(1);     // enable to display grid helper lines
    grid->end();

    win->end();
    win->resizable(grid);
    win->size_range(300, 100);
    win->show(argc, argv);
    return Fl::run();
}