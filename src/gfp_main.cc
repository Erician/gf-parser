#ifndef GFP_LOGGING_GFP_LOGGING_H_
#include "logging/gfp_logging.h"
#endif

#ifndef GFP_PAINTING_GFP_DRAWING_BOARD_H_
#include "painting/gfp_drawing_board.h"
#endif

#ifndef GFP_PAINTING_GFP_PEN_H_
#include "painting/gfp_pen.h"
#endif

#ifndef GFP_FONT_GFP_FONT_H_
#include "font/gfp_font.h"
#endif

#ifndef GFP_PAINTING_GFP_PAINTING_H_
#include "painting/gfp_painting.h"
#endif

int main(int argc,char *argv[]) {
    if(argc < 2) {
        std::cout << "Usage Error: gfp <input file> [output file]" << std::endl;
        return -1;
    }

    gfp::Font *font = new gfp::Font(argv[1]);
    if(font->Parse() != 0){
        std::cout<<"Parse Error: some error(s) happen when parsing the font file"<<std::endl;
        return -1;
    }

    gfp::DrawingBoard *drawing_board;
    if(argc < 3) {
        drawing_board = new gfp::DrawingBoard();
    }else {
        drawing_board = new gfp::DrawingBoard(argv[2]);
    }
    gfp::Painting painting(new gfp::Pen(), drawing_board, font);
    painting.Draw();
}
