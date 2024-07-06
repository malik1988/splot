//
// Created by Malik on 2024/4/19.
//
#include <nanogui/nanogui.h>
#include <iostream>
#include <memory>
#include "nplot.h"
using namespace nanogui;
class  plot_window:public Window
{
public:
    plot_window(Widget *parent, const std::string &title)
        : Window(parent, title)
    {

    }
};
class plot_screen : public Screen
{
public:
    plot_screen()
    : Screen(Vector2i(1024, 768), "nanogui example")
    {
        inc_ref();
        auto win=this->add<plot_window>("plot example");
        win->add<nplot>();
    }
};
int main(int /* argc */, char** /* argv */)
{
    try
    {
        init();

        /* scoped variables */
        {
            ref<plot_screen> app{new plot_screen};
            app->dec_ref();
            app->draw_all();
            app->set_visible(true);
            mainloop(1 / 60.f * 1000);
        }

        shutdown();
        // throw std::exception("test error");
    }
    catch (const std::exception& e)
    {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
#if defined(_WIN32)
        // MessageBoxA(nullptr, error_msg.c_str(), NULL, MB_ICONERROR | MB_OK);
#else
        std::cerr << error_msg << std::endl;
#endif
        return -1;
    } catch (...)
    {
        std::cerr << "Caught an unknown error!" << std::endl;
    }

    return 0;
}
