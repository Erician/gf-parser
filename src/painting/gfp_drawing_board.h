#ifndef GFP_PAINTING_GFP_DRAWING_BOARD_H_
#define GFP_PAINTING_GFP_DRAWING_BOARD_H_

#ifndef GFP_PAINTING_GFP_CONST_H_
#include "painting/gfp_const.h"
#endif

#ifndef GFP_PAINTING_GFP_PEN_H_
#include "painting/gfp_pen.h"
#endif

#include <fstream>

namespace gfp 
{

class DrawingBoard 
{
private:
    std::string output_file_name_;
    std::ofstream * output_file_stream_;
    std::ostream *board_;
public:
    DrawingBoard();
    DrawingBoard(std::string output_file_name);
    void SetBoard();
    void SetBoard(std::string out_file_name);
    void Draw(Pen *pen);
    void Draw(char c);
    void Put(char c);

    void Close();
};

} // namespace gfp


#endif