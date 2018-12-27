#ifndef GFP_COMMAND_GFP_FONT_H_
#define GFP_COMMAND_GFP_FONT_H_

#ifndef GFP_FONT_GFP_CHARACTER_H_
#include "font/gfp_character.h"
#endif

#ifndef GFP_COMMAND_GFP_COMMAND_H_
#include "command/gfp_command.h"
#endif

#ifndef GFP_PAINTING_GFP_DRAWING_BOARD_H_
#include "painting/gfp_drawing_board.h"
#endif

#ifndef GFP_PAINTING_GFP_PEN_H_
#include "painting/gfp_pen.h"
#endif

#include <map>

namespace gfp {

class Font {
private:
    
public:
    std::string font_file_name_;
    Command *pre_;
    Command *post_;
    Command *post_post_;
    std::map<unsigned char, CharacterLocator *> character_locator_map_;
    std::map<unsigned int, Character *> character_map_;
    Font();
    Font(std::string font_file_name);
    void SetPre(Pre *pre);
    void SetPost(Post *post);
    void SetPostPost(PostPost *post_post);
    int AddCharacterLocator(CharacterLocator *character_locator);
    int AddCharacter(Character *character);
    int Parse();
    /* draw means interprete the command of characters */
    int Draw(Pen *pen, DrawingBoard *drawing_board);
};

}

#endif