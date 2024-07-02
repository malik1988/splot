//
// Created by Malik on 2024/6/22.
//

#pragma once

#ifndef IRENDER_H
#    define IRENDER_H
#    include <tuple>

namespace splot {
class irender
{
public:
    enum class colors : int8_t
    {
        BLACK,
        BLUE,
        CYAN,
        RED,
        YELLOW,
        GREEN,
        DARKGRAY,
        LIGHTGRAY,
        WHITE,
        LIGHT_BLUE,

        BROWN,
        ORANGE,
        PINK,
        PURPLE,

        UNSET = -1,
    };

    enum class alignments : int8_t
    {
        LEFT,
        CENTER,
        RIGHT,
        TOP,
        BOTTOM
    };

    virtual ~irender() = default;

    /**
     * !!! DO NOT try to destruct this context, it's just a reference. It should
     * be fully managed outof this class!!!
     * @param context reference of the draw context
     * @return the render pointer
     */
    virtual irender* init(const void* context) = 0;

    virtual void set_bg_color(colors color) = 0;

    virtual void set_fg_color(colors color) = 0;

    virtual void move_to(float x, float y) = 0;

    virtual void line_to(float x, float y) = 0;

    /**
     *  get the width and height of the draw area
     * @return width,height
     */
    virtual std::tuple<float, float> get_size() = 0;

    virtual void draw_rect(float l_x, float l_y, float r_x, float r_y, bool fill, float radius) = 0;

    /**
     * begin pattern for line drawing,
     * always remmber to envelop with a `end_line_style`
     * @param width width of the next drawing line
     * @param color color of the next drawing line
     */
    virtual void begin_line_style(float width, irender::colors color) = 0;

    virtual void end_line_style() = 0;

    virtual void set_text_style(float font_size, irender::colors color) = 0;

    virtual void set_text_justify(int h, int v) = 0;

    virtual void draw_text(float x, float y, const char* text) = 0;

    virtual void swap_buffer() = 0;

    /**
     * get left top right bottom
     * using left top as orgin zero point and right bottom as maxium point of
     * the canvas
     * @return left,top,right,bottom
     */
    virtual std::tuple<float, float, float, float> get_bounds() = 0;

    virtual void refresh_view() = 0;
};
}   // namespace splot
#endif   // IRENDER_H
