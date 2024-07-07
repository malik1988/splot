//
// Created by Malik on 2024/4/19.
//
#include "nplot.h"
#include <iostream>
#include <memory>
#include <nanogui/graph.h>
#include <nanogui/nanogui.h>
using namespace nanogui;

int WIN_WIDTH = 800, WIN_HEIGHT = 600;

class plot_screen : public Screen
{
private:
    ref<Shader>     m_shader;
    ref<RenderPass> m_render_pass;

public:
    plot_screen()
        : Screen(Vector2i(WIN_WIDTH, WIN_HEIGHT), "nanogui example")
    {
        inc_ref();
        auto plot = add<nplot>("plot nanogui");
        plot->set_fixed_size({WIN_WIDTH, WIN_HEIGHT});
        plot->manipulator()
            ->with_axes_mark(true)
            ->with_grid_h(true)
            ->with_grid_v(true)
            ->with_rect(true)
            ->with_legend(true);
        plot->plot();
        plot->plot_more();

        perform_layout();
    }
};
int main(int /* argc */, char** /* argv */)
{
    try {
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
    catch (const std::exception& e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
#if defined(_WIN32)
        // MessageBoxA(nullptr, error_msg.c_str(), NULL, MB_ICONERROR | MB_OK);
#else
        std::cerr << error_msg << std::endl;
#endif
        return -1;
    }
    catch (...) {
        std::cerr << "Caught an unknown error!" << std::endl;
    }

    return 0;
}
