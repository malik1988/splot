//
// Created by Malik on 2024/4/19.
//
#include "nplot.h"
#include <iostream>
#include <memory>
#include <nanogui/graph.h>
#include <nanogui/nanogui.h>
using namespace nanogui;
class plot_window : public Window
{
public:
    plot_window(Widget* parent, const std::string& title)
        : Window(parent, title)
    {}
};
class plot_screen : public Screen
{
private:
    ref<Shader>     m_shader;
    ref<RenderPass> m_render_pass;

public:
    plot_screen()
        : Screen(Vector2i(1024, 768), "nanogui example")
    {
        inc_ref();
        auto plot = add<nplot>("plot nanogui");
        plot->set_fixed_size({800, 600});
        plot->manipulator()
            ->with_axes_mark(true)
            ->with_grid_h(true)
            ->with_grid_v(true)
            ->with_rect(true)
            ->with_legend(true);
        plot->plot();
        plot->plot_more();


        perform_layout();

#if 0
#    pragma region 创建阴影
        /* All NanoGUI widgets are initialized at this point. Now
              create shaders to draw the main window contents.

              NanoGUI comes with a simple wrapper around OpenGL 3, which
              eliminates most of the tedious and error-prone shader and buffer
              object management.
           */

        m_render_pass = new RenderPass({this});
        m_render_pass->set_clear_color(0, Color(0.3f, 0.3f, 0.32f, 1.f));

        m_shader = new Shader(m_render_pass,

                              /* An identifying name */
                              "a_simple_shader",

#    if defined(NANOGUI_USE_OPENGL)
                              R"(/* Vertex shader */
            #version 330
            uniform mat4 mvp;
            in vec3 position;
            void main() {
                gl_Position = mvp * vec4(position, 1.0);
            })",

                              /* Fragment shader */
                              R"(#version 330
            out vec4 color;
            uniform float intensity;
            void main() {
                color = vec4(vec3(intensity), 1.0);
            })"
#    elif defined(NANOGUI_USE_GLES)
                              R"(/* Vertex shader */
            precision highp float;
            uniform mat4 mvp;
            attribute vec3 position;
            void main() {
                gl_Position = mvp * vec4(position, 1.0);
            })",

                              /* Fragment shader */
                              R"(precision highp float;
            uniform float intensity;
            void main() {
                gl_FragColor = vec4(vec3(intensity), 1.0);
            })"
#    elif defined(NANOGUI_USE_METAL)
                              R"(using namespace metal;
            struct VertexOut {
                float4 position [[position]];
            };

            vertex VertexOut vertex_main(const device packed_float3 *position,
                                         constant float4x4 &mvp,
                                         uint id [[vertex_id]]) {
                VertexOut vert;
                vert.position = mvp * float4(position[id], 1.f);
                return vert;
            })",

                              /* Fragment shader */
                              R"(using namespace metal;
            fragment float4 fragment_main(const constant float &intensity) {
                return float4(intensity);
            })"
#    endif
        );

        uint32_t indices[3 * 2] = {0, 1, 2, 2, 3, 0};

        float positions[3 * 4] = {-1.f, -1.f, 0.f, 1.f, -1.f, 0.f, 1.f, 1.f, 0.f, -1.f, 1.f, 0.f};

        m_shader->set_buffer("indices", VariableType::UInt32, {3 * 2}, indices);
        m_shader->set_buffer("position", VariableType::Float32, {4, 3}, positions);
        m_shader->set_uniform("intensity", 0.8f);
#    pragma endregion
#endif
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
