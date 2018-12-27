#ifndef GFP_FONT_GFP_CHARACTER_H_
#define GFP_FONT_GFP_CHARACTER_H_

#ifndef GFP_COMMAND_GFP_COMMAND_H_
#include "command/gfp_command.h"
#endif

#ifndef GFP_PAINTING_GFP_DRAWING_BOARD_H_
#include "painting/gfp_drawing_board.h"
#endif

#ifdef GFP_PAINTING_GFP_PEN_H_
#include "painting/gfp_pen.h"
#endif

#include <fstream> 
#include <vector>

namespace gfp{

class Character{
private:

public:
    unsigned int character_code_;
    std::vector<gfp::Command *> commands_;
    Character();
    void SetCharacterCode(unsigned int character_code);
    unsigned int GetCharacterCode();
    void AddCommand(gfp::Command* command);
    Character * Parse(std::ifstream *ifs);
    int Draw(Pen *pen, DrawingBoard *drawing_board);
};

} // namespace gfp


#endif