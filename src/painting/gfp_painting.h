#ifndef GFP_PAINTING_GFP_PAINTING_H_
#define GFP_PAINTING_GFP_PAINTING_H_

#ifndef GFP_PAINTING_GFP_DRAWING_BOARD_H_
#include "painting/gfp_drawing_board.h"
#endif

#ifndef GFP_PAINTING_GFP_PEN_H_
#include "painting/gfp_pen.h"
#endif

#ifndef GFP_FONT_GFP_FONT_H_
#include "font/gfp_font.h"
#endif

#ifndef GFP_COMMAND_GFP_COMMAND_H_
#include "COMMAND/gfp_command.h"
#endif


#include <iostream>

namespace gfp
{

class Painting {
private:
    Pen *pen_;
    DrawingBoard *drawing_board_;
    Font *font_;
public:
    Painting();
    Painting(Pen *pen, DrawingBoard *drawing_board, Font *font);
    int Draw();
};

} // namespace gfp

#endif