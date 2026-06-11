#pragma once

#include "GlobalVariables.h"
#include "Input/Input.h"
#include "System/HTTP.h"

struct HTML_style {
    uint16_t color, background_color, border_color;
    // Should also define a variable for an image background
    uint8_t border_size = 0, padding_x = 0, padding_y = 0;
    
    #define IS_TX_COLOR_DEF 32768
    #define IS_BG_COLOR_DEF 16384
    #define IS_BD_COLOR_DEF 8192
    #define BOLD            4096
    //#define ITALIC        2048
    #define STRIKED         1024
    #define UNDERLINED      512
    #define SUBSCRIPT       256
    #define SUPERSCRIPT     128

    uint16_t definedColors = 0;
};

class HTML_item {
public:
    uint16_t x, y, w, h;
    HTML_style style;

    /*
    * Renders the HTML item
    * @param renderWindow Since the render methods mess with the viewport, this parameter keeps track of the original renderer window so that we can tell it not to render items that go outside of the box
    * @param style_override Overrides the default style (Used when the content being rendered has a parent tag with a specified style)
    * @param style_override Only overrides the style of items that don't have a specified style when false, overrides all items inside when true
    */
    virtual void render(uint16_t offset_x, uint16_t offset_y, Viewport *renderWindow,
                        HTML_style *style_override = nullptr, bool overrideAll = false);
};

class HTML_text : public HTML_item { // Not associated to any tag
    NString content;
    void render(uint16_t offset_x, uint16_t offset_y, Viewport *renderWindow,
                HTML_style *style_override = nullptr, bool overrideAll = false) override;
};

class HTML_P : public HTML_item { // Also used for any header tag other than <h1> (since adding different sized fonts takes too much storage)
public:
    std::vector<HTML_item*> content;
    void render(uint16_t offset_x, uint16_t offset_y, Viewport *renderWindow,
                HTML_style *style_override = nullptr, bool overrideAll = false) override;
};