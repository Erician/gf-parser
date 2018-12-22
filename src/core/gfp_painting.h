#ifndef GFP_CORE_GFP_PAINTING_H_
#define GFP_CORE_GFP_PAINTING_H_

#ifndef GFP_CORE_GFP_BOARD_H_
#include "core/gfp_board.h"
#endif

#include <iostream>

namespace gfp
{

class Painting {
private:
    int painter_switch_;    /* black(1) or white(0) */
    
    Board board;
    void InitBoard();

public:
    Painting();
    int GetPainterSwitch();
    void SetPainterSwitch(int painter_switch);
    void ChangePainterSwitch();
    void Draw();

};

} // namespace gfp

#endif