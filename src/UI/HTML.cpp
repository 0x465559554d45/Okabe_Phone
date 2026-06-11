#include "HTML.h"

void applyOverrideStyle(HTML_style *src, HTML_style *dest, bool allColors = false,
                        bool passBorders = false) {
    if(passBorders)
        dest->definedColors |= src->definedColors;
    else
        dest->definedColors |= src->definedColors-(src->definedColors&IS_BD_COLOR_DEF);
    if((src->definedColors&IS_TX_COLOR_DEF) && !(dest->definedColors&IS_TX_COLOR_DEF))
        dest->color = src->color;
    if((src->definedColors&IS_BG_COLOR_DEF) && !(dest->definedColors&IS_BG_COLOR_DEF))
        dest->background_color = src->background_color;
    if(passBorders && (!dest->border_size)) {
        dest->border_size  = src->border_size;
        dest->border_color = src->border_color;
    }
}

void HTML_item::render(uint16_t offset_x, uint16_t offset_y,
                       Viewport *renderWindow, HTML_style *style_override,
                       bool overrideAll) { return; };

void HTML_text::render(uint16_t offset_x, uint16_t offset_y,
                       Viewport *renderWindow, HTML_style *style_override,
                       bool overrideAll) {
    HTML_style curStyle = style;
    if(style_override)
        applyOverrideStyle(style_override, &curStyle);

    // We don't need to set a viewport, but we need this to not render outside of the rendering window
    Viewport view = tft.getViewport();
    int viewX = view.x+x+offset_x+renderWindow->x;
    int viewY = view.y+y+offset_y+renderWindow->y;
    int viewW = (w>view.w?view.w:w)-(offset_x*2);
    int viewH = (w>view.h?view.h:h)-(offset_y*2);

    if(viewX>(renderWindow->x+renderWindow->w) || viewY>(renderWindow->y+renderWindow->h)) { return; }
    viewW = (viewX+viewW > renderWindow->x+renderWindow->w) ? renderWindow->w-viewX : viewW;
    viewH = (viewY+viewH > renderWindow->y+renderWindow->h) ? renderWindow->h-viewY : viewH;

}

void HTML_P::render(uint16_t offset_x, uint16_t offset_y,
                    Viewport *renderWindow, HTML_style *style_override,
                    bool overrideAll) {
    Viewport prevView = tft.getViewport();

    // Set the viewport
    int viewX = prevView.x+x+offset_x+renderWindow->x;
    int viewY = prevView.y+y+offset_y+renderWindow->y;
    int viewW = (w>prevView.w?prevView.w:w)-(offset_x*2);
    int viewH = (w>prevView.h?prevView.h:h)-(offset_y*2);

    // Do not render outside of the rendering window
    if(viewX>(renderWindow->x+renderWindow->w) || viewY>(renderWindow->y+renderWindow->h)) { return; }
    viewW = (viewX+viewW > renderWindow->x+renderWindow->w) ? renderWindow->w-viewX : viewW;
    viewH = (viewY+viewH > renderWindow->y+renderWindow->h) ? renderWindow->h-viewY : viewH;
    tft.setViewport(viewX, viewY, viewW, viewH);

    HTML_style curStyle = style;
    if(style_override)
        applyOverrideStyle(style_override, &curStyle);

    for(unsigned int i = 0; i < content.size(); i++)
        content[i]->render(0, 0, renderWindow, style_override, overrideAll);
    tft.setViewport(prevView);
} 
