#ifndef GFP_PAINTING_GFP_PAINTING_H_
#include "painting/gfp_painting.h"
#endif

namespace gfp{

Painting::Painting(){
    pen_ = NULL;
    drawing_board_ = NULL;
    font_ = NULL;
}

Painting::Painting(Pen *pen, DrawingBoard *drawing_board, Font *font){
    pen_ = pen;
    drawing_board_ = drawing_board;
    font_ = font;
}

int Painting::Draw() {
    return font_->Draw(pen_, drawing_board_);
}

} // name gpf
